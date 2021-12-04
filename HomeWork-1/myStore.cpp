#include "interface.h"
#include "consoleLogger.h"

/// This is sample empty implementation you can place your solution here or delete this and include tests to your solution

#include "myStore.h"




Store *createStore() {
	return new MyStore();
}