#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>
#include "interface.h"
#include "consoleLogger.h"
#include "myClient.h"
#include "priorityQueue.h"
#include "event.h"


const int RESTOCK_TIME = 60;
const int RESTOCK_AMOUNT = 100;

class MyStore : public Store {

	private:
	int bananas; ///< Amount of bananas in the store
	int schweppes; ///< Amount of schweppes in the store
	int workers; ///< Amount of workers in the store
    int index; ///< How many clients we have
	int minute; ///< Current minute
	size_t workersGoingBanana; ///< How many workers are going for bananas
	size_t workersGoingSchweppes; ///< How many workers are going for schweppes
	PriorityQueue<Event*> events; ///< Events happening chronologically
	PriorityQueue<int> nextWorkerBack; ///< Keeps the time when workers are coming back
	std::vector<int> pastClients;  ///< Keeps track of the clients that have been served

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
	void advance();

	// Service related

	void service(MyClient&);
	bool need(int, int);
	void needForce(int&, int&);
	void updateStock(const ResourceType);
	
	// Action related

	void sendWorker(const ResourceType);
	void workerBack(const ResourceType);
	void clientDepart(const MyClient&);


	bool checkForPastClients(const size_t&);
	virtual int getBanana() const override;

	virtual int getSchweppes() const override;
};