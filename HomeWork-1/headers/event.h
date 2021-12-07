#pragma once
#include "myClient.h"
#include "interface.h"

struct Event {

    enum Type {
        WorkerSend, WorkerBack, ClientDepart,
        ClientArrive, MaxTimeReached, Skip, CheckAgain
    };

    struct Worker {
        ResourceType resource;
    };

    Type type;
    int minute;
    MyClient client;
    Worker worker;
};