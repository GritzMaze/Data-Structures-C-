#include "interface.h"
#include "consoleLogger.h"
#include "myStore.h"

MyStore::MyStore()
{
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
}

MyStore::~MyStore()
{
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
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
	// TO-DO
	// Throws exceptions
	// Rewrite
	// Also wait for previous customer to get away
	while (events.first().minute <= minute)
	{
		Event temp = events.dequeue();
		this->minute = temp.minute;
		if (temp.type == Event::Skip)
		{
			continue;
		}
		if (temp.type == Event::ClientArrive || temp.type == Event::MaxTimeReached)
		{
			this->service(temp.client);
		}
		if (temp.type == Event::WorkerBack)
		{
			workerBack(temp.worker.resource);
			this->service(current);
		}
	}
}

// maxwaittime event sushto da preprashta tuk
void MyStore::service(MyClient &client)
{
	int maxWaitTimeMin = client.maxWaitTimeMin;
	if (maxWaitTimeMin <= this->minute)
	{
		needForce(client.banana, client.schweppes);
		this->clientDepart(client);
	}
	else
	{
		if (need(client.banana, client.schweppes))
		{
			this->clientDepart(client);
			//to do
			// delete maxWaitTime event from events
		}
		else
		{
			current = client;
		}
	}
}


// TO-DO
// Rewrite (Not working properly)
bool MyStore::need(int &bananas, int &schweppes)
{
	if (bananas <= this->bananas && schweppes <= this->schweppes)
	{
		this->needForce(bananas, schweppes);
		return true;
	}
	else
	{
		if (bananas > 0 && !isWorkerGoingBanana)
		{
			if (bananas > this->bananas)
			{
				// if (this->bananas + bananas >= this->schweppes + schweppes)
				// {
				sendWorker(ResourceType::banana);
				isWorkerGoingBanana = true;
				return false;
				// }
				// else
				// {
				// 	sendWorker(ResourceType::schweppes);
				// 	return false;
				// }
			}
			else
			{
				if (isWorkerGoingSchweppes)
					return false;
				sendWorker(ResourceType::schweppes);
				isWorkerGoingSchweppes = true;
				return false;
			}
		}
		else
		{
			if (isWorkerGoingSchweppes)
				return false;
			sendWorker(ResourceType::schweppes);
			isWorkerGoingSchweppes = true;
			return false;
		}
	}
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

		Event ev1;
		ev1.type = Event::ClientArrive;
		ev1.minute = temp.arriveMinute;
		ev1.client = temp;

		this->events.enqueue(ev1, ev1.minute);

		Event ev2;
		ev2.type = Event::MaxTimeReached;
		ev2.minute = temp.maxWaitTimeMin;
		ev2.client = temp;

		this->events.enqueue(ev2, ev2.minute);
		counter++;
	}
}

void MyStore::updateStock(const ResourceType type)
{
	if (type == ResourceType::banana)
	{
		this->bananas += 60;
		isWorkerGoingBanana = false;
	}
	else
		this->schweppes += 60;
		isWorkerGoingSchweppes = false;
}

void MyStore::sendWorker(const ResourceType type)
{
	if (this->workers > 0)
	{
		Event ev;
		ev.type = Event::WorkerBack;
		ev.minute = this->minute + 60;
		ev.worker.resource = type;
		events.enqueue(ev, ev.minute);
		this->workers--;
		//actionHandler->onWorkerSend(this->minute, type);
		consoleLogger->onWorkerSend(this->minute, type);
	}
}

void MyStore::workerBack(const ResourceType type)
{
	this->workers++;
	updateStock(type);
	//actionHandler->onWorkerBack(this->minute, type);
	consoleLogger->onWorkerBack(this->minute, type);
}

void MyStore::clientDepart(const MyClient &client)
{
	//actionHandler->onClientDepart(client.index, this->minute, client.banana, client.schweppes);
	consoleLogger->onClientDepart(client.index, this->minute, client.banana, client.schweppes);
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