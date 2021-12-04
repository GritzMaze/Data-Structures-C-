#pragma once
#include "interface.h"

struct ConsoleLogger : public ActionHandler {
	
    void onWorkerSend(int minute, ResourceType ResourceType) override {
        std::cout << "W" << " " << minute << " " << ResourceType << std::endl; 
    }

    void onWorkerBack(int minute, ResourceType ResourceType) override {
        std::cout << "D" << " " << minute << " " << ResourceType << std::endl;
    }

    void onClientDepart(int index, int minute, int banana, int schweppes) override {
        std::cout << index << " " << minute << " " << banana << " " << schweppes << std::endl;
    }
};