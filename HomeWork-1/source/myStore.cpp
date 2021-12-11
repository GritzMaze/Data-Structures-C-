#include "../headers/interface.h"
#include "../headers/consoleLogger.h"
#include "../headers/myStore.h"

MyStore::MyStore()
{
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
	this->minute = 0;
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
	this->workersGoingBanana = 0;
	this->workersGoingSchweppes = 0;

	delete this->consoleLogger;
	actionHandler = nullptr;
	consoleLogger = nullptr;
}

/// Initialize the store

void MyStore::init(int workerCount, int startBanana, int startSchweppes)
{
	if (workerCount < 0 || startBanana < 0 || startSchweppes < 0)
	{
		throw std::out_of_range("Negative value");
	}
	this->bananas = startBanana;
	this->schweppes = startSchweppes;
	this->workers = workerCount;
}

/// Cycle through the whole application

void MyStore::advance()
{
	while (!events.isEmpty())
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

/// Goes to @minute and does all the action to this minute

void MyStore::advanceTo(int minute)
{
	/// if we move back in time
	if (minute < this->minute)
		throw std::out_of_range("Invalid input");

	/// while there are events left
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

/// Service a client

void MyStore::service(MyClient &client)
{
	///if the store has what the client wants, he takes it and leave
	if (need(client.banana, client.schweppes))
	{
		this->clientDepart(client);
	}
	else
	{
		/// push after the closest workerback event
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

/// Checks if clients need anything, then determine what worker should be sent

bool MyStore::need(int bananas, int schweppes)
{
	int bananasComing = this->workersGoingBanana * RESTOCK_AMOUNT;
	int schweppesComing = this->workersGoingSchweppes * RESTOCK_AMOUNT;

	/// If the event actually need something
	bool flag = (this->bananas + bananasComing > bananas) && (this->schweppes + schweppesComing > schweppes);

	/// IF the store has what the client wants
	if (bananas <= this->bananas && schweppes <= this->schweppes)
	{
		this->needForce(bananas, schweppes);
		return true;
	}

	while (this->workers && (bananas > 0 || schweppes > 0) && !flag)
	{
		/// Do we need bananas
		if (!(this->bananas + bananasComing >= bananas))
		{
			/// Do we need bananas more than schweppes
			if (this->bananas + bananas >= this->schweppes + schweppes && bananas)
			{
				sendWorker(ResourceType::banana);
				if (bananas > 100)
					bananas -= 100;
				else
					bananas = 0;
			}
			else
			{	/// else we check do we need schweppes
				if (!(this->schweppes + schweppesComing >= schweppes))
				{
					sendWorker(ResourceType::schweppes);
					if (schweppes > 100)
						schweppes -= 100;
					else
						schweppes = 0;
				}
			}
		}
		else
		{
			/// Do we need schweppes
			if (!(this->schweppes + schweppesComing >= schweppes))
			{
				sendWorker(ResourceType::schweppes);
				if (schweppes > 100)
					schweppes -= 100;
				else
					schweppes = 0;
			}
		}

		/// If we still need something
		flag = (this->bananas + bananasComing >= bananas) && (this->schweppes + schweppesComing >= schweppes);
	}
	return false;
}

/// Client takes whats available

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

/// Adding clients to the store

void MyStore::addClients(const Client *clients, int count = 1)
{
	int counter = 0;
	while (counter != count)
	{
		MyClient temp;
		temp.arriveMinute = clients[counter].arriveMinute;
		temp.banana = clients[counter].banana;
		temp.schweppes = clients[counter].schweppes;
		temp.maxWaitTimeMin = temp.arriveMinute + clients[counter].maxWaitTime;
		temp.index = this->index++;

		if (temp.arriveMinute < 0 || temp.banana < 0 || temp.schweppes < 0 || temp.maxWaitTimeMin < 0)
		{
			throw std::out_of_range("Negative value");
		}

		/// Creating event for client arrival
		Event *ev1 = new Event();
		ev1->type = Event::ClientArrive;
		ev1->minute = temp.arriveMinute;
		ev1->client = temp;

		this->events.enqueue(ev1, ev1->minute + 10);

		/// Creating event for client max wait time
		Event *ev2 = new Event();
		ev2->type = Event::MaxTimeReached;
		ev2->minute = temp.maxWaitTimeMin;
		ev2->client = temp;

		this->events.enqueue(ev2, ev2->minute + 12);
		counter++;
	}
}

/// Updating the resources in the store

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

/// Sending a worker for resource

void MyStore::sendWorker(const ResourceType type)
{

	/// if there is available worker
	if (this->workers)
	{
		/// Creating event for when a worker comes back
		Event *ev = new Event();
		ev->type = Event::WorkerBack;
		ev->minute = this->minute + RESTOCK_TIME;
		ev->worker.resource = type;
		this->events.enqueue(ev, ev->minute + 11);
		this->workers--;
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

/// When a worker comes back

void MyStore::workerBack(const ResourceType type)
{
	this->workers++;

	nextWorkerBack.dequeue();

	updateStock(type);

	if (actionHandler)
		actionHandler->onWorkerBack(this->minute, type);
	consoleLogger->onWorkerBack(this->minute, type);
}

/// When a client departs

void MyStore::clientDepart(const MyClient &client)
{
	pastClients.push_back(client.index);

	if (actionHandler)
		actionHandler->onClientDepart(client.index, this->minute, client.banana, client.schweppes);
	consoleLogger->onClientDepart(client.index, this->minute, client.banana, client.schweppes);
}

/// Checking if a client has already left, we skip the event

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