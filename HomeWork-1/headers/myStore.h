#pragma once

#include <vector>
#include "interface.h"
#include "consoleLogger.h"
#include "MyClient.h"
#include "priorityQueue.h"
#include "event.h"

const int RESTOCK_TIME = 60;
const int RESTOCK_AMOUNT = 100;

class MyStore : public Store {

	private:
	int bananas;
	int schweppes;
	int workers;
    int index;
	int currentIndex;
	int minute;
	size_t workersGoingBanana;
	size_t workersGoingSchweppes;
	PriorityQueue<Event*> events;
	PriorityQueue<int> nextWorkerBack;
	std::vector<int> pastClients;

	ActionHandler *actionHandler = nullptr;
	ConsoleLogger *consoleLogger;

	public:
    MyStore();
    ~MyStore();


	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override;
	void addClients(const Client *clients, int count) override;
	void advanceTo(int minute) override;
	void service(MyClient&);
	bool need(int&, int&);
	void needForce(int&, int&);
	void updateStock(const ResourceType);
	
	void sendWorker(const ResourceType, size_t);
	void workerBack(const ResourceType);
	void clientDepart(const MyClient&);


	bool checkForPastClients(const size_t&);
	virtual int getBanana() const;

	virtual int getSchweppes() const;
};