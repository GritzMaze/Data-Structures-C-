#pragma once

#include "interface.h"

struct MyClient : public Client {
    int maxWaitTimeMin;
    int index;
};