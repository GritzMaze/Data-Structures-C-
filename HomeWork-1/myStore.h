#pragma once

#include "interface.h"
#include "consoleLogger.h"

class MyStore : public Store {

	private:
	int bananas;
	int schweppes;
	int workers;
    int index;

	ActionHandler *actionHandler = nullptr;
	ConsoleLogger *consoleLogger = nullptr;

	public:
    MyStore();
    ~MyStore();


	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void setConsoleLogger(ConsoleLogger *logger) {
		consoleLogger = logger;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override;
	void addClients(const Client *clients, int count) override;
	void advanceTo(int minute) override;

	virtual int getBanana() const;

	virtual int getSchweppes() const;
};