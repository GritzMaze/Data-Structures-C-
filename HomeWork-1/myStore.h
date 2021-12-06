#pragma once

#include <vector>
#include "interface.h"
#include "consoleLogger.h"
#include "MyClient.h"
#include "priorityQueue.h"
#include "event.h"

class MyStore : public Store {

	private:
	int bananas;
	int schweppes;
	int workers;
    int index;
	int currentIndex;
	int minute = 0;
	bool isWorkerGoingBanana;
	bool isWorkerGoingSchweppes;
	PriorityQueue<Event*> events;
	PriorityQueue<int> nextWorkerBack;
	MyClient current;

	ActionHandler *actionHandler = nullptr;
	ConsoleLogger *consoleLogger = new ConsoleLogger();

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
	
	void sendWorker(const ResourceType);
	void workerBack(const ResourceType);
	void clientDepart(const MyClient&);

	virtual int getBanana() const;

	virtual int getSchweppes() const;
};