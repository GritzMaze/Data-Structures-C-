#include "../headers/interface.h"
#include "../headers/consoleLogger.h"
#include "../headers/myStore.h"

MyStore::MyStore() {
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
	this->minute = 0;
	this->currentIndex = 0;
	this->workersGoingBanana = 0;
	this->workersGoingSchweppes = 0;
	this->consoleLogger = new ConsoleLogger();
}

MyStore::~MyStore()
{
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
	this->minute = 0;
	this->currentIndex = 0;
	this->workersGoingBanana = 0;
	this->workersGoingSchweppes = 0;

	delete this->consoleLogger;
	actionHandler = nullptr;
	consoleLogger = nullptr;
}

void MyStore::init(int workerCount, int startBanana, int startSchweppes)
{
	this->bananas = startBanana;
	this->schweppes = startSchweppes;
	this->workers = workerCount;
}

void MyStore::advanceTo(int minute)
{
	while (!events.isEmpty() && events.first()->minute <= minute)
	{
		Event *temp = events.dequeue();
		this->minute = temp->minute;
		if (temp->type == Event::ClientArrive || temp->type == Event::CheckAgain)
		{

			if (checkForPastClients(temp->client.index))
				continue;

			this->service(temp->client);
		}
		else if (temp->type == Event::WorkerBack)
		{
			workerBack(temp->worker.resource);
		}
		else if (temp->type == Event::MaxTimeReached)
		{
			if (checkForPastClients(temp->client.index))
				continue;
			needForce(temp->client.banana, temp->client.schweppes);
			this->clientDepart(temp->client);
		}
	}
}

void MyStore::service(MyClient &client)
{
	if (need(client.banana, client.schweppes))
	{
		this->clientDepart(client);
	}
	else
	{
		//push after the closest workerback event
		if (!nextWorkerBack.isEmpty())
		{
			bool waitingTime = nextWorkerBack.first() <= client.maxWaitTimeMin;
			if (waitingTime)
			{
				Event *ev = new Event();
				ev->type = Event::CheckAgain;
				ev->minute = nextWorkerBack.first();
				ev->client = client;
				events.enqueue(ev, ev->minute + 12);
			}
		}
	}
}

// TO-DO
// Rewrite (Not working properly)
bool MyStore::need(int &bananas, int &schweppes)
{
	int bananasComing = this->workersGoingBanana * RESTOCK_AMOUNT;
	int schweppesComing = this->workersGoingSchweppes * RESTOCK_AMOUNT;
	if (bananas <= this->bananas && schweppes <= this->schweppes)
	{
		this->needForce(bananas, schweppes);
		return true;
	}
	else
	{
		if (!(this->bananas + bananasComing >= bananas))
		{
			if (this->bananas + bananas >= this->schweppes + schweppes)
			{
					sendWorker(ResourceType::banana, ((bananas - (this->bananas + bananasComing))/RESTOCK_AMOUNT) + 1);
					return false;
			}
		}
		if (!(this->schweppes + schweppesComing >= schweppes))
		{
					sendWorker(ResourceType::schweppes, ((schweppes - (this->schweppes + schweppesComing))/RESTOCK_AMOUNT) + 1);
					return false;
		}
	}
	return false;
}

void MyStore::needForce(int &bananas, int &schweppes)
{
	if (bananas > this->bananas)
	{
		bananas = this->bananas;
		this->bananas = 0;
	}
	else
	{
		this->bananas = this->bananas - bananas;
	}

	if (schweppes > this->schweppes)
	{
		schweppes = this->schweppes;
		this->schweppes = 0;
	}
	else
	{
		this->schweppes = this->schweppes - schweppes;
	}
}

void MyStore::addClients(const Client *clients, int count = 1)
{
	int counter = 0;
	while (counter != count)
	{
		MyClient temp;
		temp.arriveMinute = (*(clients + counter)).arriveMinute;
		temp.banana = (*(clients + counter)).banana;
		temp.schweppes = (*(clients + counter)).schweppes;
		temp.maxWaitTimeMin = temp.arriveMinute + (*(clients + counter)).maxWaitTime;
		temp.index = index++;

		Event *ev1 = new Event();
		ev1->type = Event::ClientArrive;
		ev1->minute = temp.arriveMinute;
		ev1->client = temp;

		this->events.enqueue(ev1, ev1->minute + 10);

		Event *ev2 = new Event();
		ev2->type = Event::MaxTimeReached;
		ev2->minute = temp.maxWaitTimeMin;
		ev2->client = temp;

		this->events.enqueue(ev2, ev2->minute + 12);
		counter++;
	}
}

void MyStore::updateStock(const ResourceType type)
{
	if (type == ResourceType::banana)
	{
		this->bananas += RESTOCK_AMOUNT;
	}
	else
	{
		this->schweppes += RESTOCK_AMOUNT;
	}
}

void MyStore::sendWorker(const ResourceType type, size_t workersNeeded)
{

	while (this->workers > 0 && workersNeeded > 0)
	{
		Event *ev = new Event();
		ev->type = Event::WorkerBack;
		ev->minute = this->minute + RESTOCK_TIME;
		ev->worker.resource = type;
		this->events.enqueue(ev, ev->minute + 11);
		this->workers--;
		workersNeeded--;
		if (type == ResourceType::banana)
			workersGoingBanana++;
		else
			workersGoingSchweppes++;
		nextWorkerBack.enqueue(ev->minute, 0);

		if (actionHandler)
			actionHandler->onWorkerSend(this->minute, type);
		consoleLogger->onWorkerSend(this->minute, type);
	}
}

void MyStore::workerBack(const ResourceType type)
{
	this->workers++;

	nextWorkerBack.dequeue();

	updateStock(type);

	if (actionHandler)
		actionHandler->onWorkerBack(this->minute, type);
	consoleLogger->onWorkerBack(this->minute, type);
}

void MyStore::clientDepart(const MyClient &client)
{
	pastClients.push_back(client.index);

	if (actionHandler)
		actionHandler->onClientDepart(client.index, this->minute, client.banana, client.schweppes);
	consoleLogger->onClientDepart(client.index, this->minute, client.banana, client.schweppes);
}

bool MyStore::checkForPastClients(const size_t &clientIndex)
{
	for (int &index : pastClients)
	{
		if (index == clientIndex)
		{
			return true;
		}
	}
	return false;
}

int MyStore::getBanana() const
{
	return this->bananas;
}

int MyStore::getSchweppes() const
{
	return this->schweppes;
}

Store *createStore()
{
	return new MyStore();
}