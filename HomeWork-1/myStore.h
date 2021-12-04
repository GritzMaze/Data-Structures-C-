#pragma once

#include "interface.h"
#include "consoleLogger.h"

class MyStore : public Store {

	private:
	int bananas;
	int schweppes;
	int workers;

	ActionHandler *actionHandler = nullptr;
	ConsoleLogger *consoleLogger = nullptr;

	public:
	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void setConsoleLogger(ConsoleLogger *logger) {
		consoleLogger = logger;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override {
		
	}

	void addClients(const Client *clients, int count) override {
		
	}

	void advanceTo(int minute) override {
		actionHandler->onWorkerSend(0, ResourceType::banana);
		actionHandler->onWorkerBack(0, ResourceType::schweppes);
		actionHandler->onClientDepart(0, 0, 1, 2);
	}

	virtual int getBanana() const {
		return this->bananas;
	}

	virtual int getSchweppes() const {
		return this->schweppes;
	}
};