#pragma once
#include <iostream>
#include <cstring>
#include "interface.h"

struct ConsoleLogger : public ActionHandler {
	
    void onWorkerSend(int minute, ResourceType ResourceType) override {
        std::cout << "W" << " " << minute << " " << toString(ResourceType) << std::endl; 
    }

    void onWorkerBack(int minute, ResourceType ResourceType) override {
        std::cout << "D" << " " << minute << " " << toString(ResourceType) << std::endl;
    }

    void onClientDepart(int index, int minute, int banana, int schweppes) override {
        std::cout << index << " " << minute << " " << banana << " " << schweppes << std::endl;
    }

    const std::string toString(ResourceType ResourceType) const {

        switch(ResourceType) {
            case ResourceType::banana:
            return "banana";
            break;
            case ResourceType::schweppes:
            return "schweppes";
            break;
            default:
            throw std::logic_error("Bad enum type");
        }

    }
};