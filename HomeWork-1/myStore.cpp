#include "interface.h"
#include "consoleLogger.h"
#include "myStore.h"

/// This is sample empty implementation you can place your solution here or delete this and include tests to your solution

MyStore::MyStore() {
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
}

MyStore::~MyStore() {
	this->bananas = 0;
	this->schweppes = 0;
	this->workers = 0;
	this->index = 0;
}


void MyStore::init(int workerCount, int startBanana, int startSchweppes) {
	this->bananas = startBanana;
	this->schweppes= startSchweppes;
}

void MyStore::advanceTo(int minute)
{
	actionHandler->onWorkerSend(0, ResourceType::banana);
	actionHandler->onWorkerBack(0, ResourceType::schweppes);
	actionHandler->onClientDepart(0, 0, 1, 2);
}

void MyStore::addClients(const Client *clients, int count = 1) {
	
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