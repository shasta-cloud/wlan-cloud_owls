//
// Created by stephane bourque on 2021-03-13.
//

#ifndef UCENTRAL_CLNT_SIMULATOR_H
#define UCENTRAL_CLNT_SIMULATOR_H
#include <string>
#include <map>
#include <set>

#include "Poco/Thread.h"

#include "uCentralClient.h"

class Simulator : public Poco::Runnable {
public:

    Simulator(uint64_t Index,std::string SerialStart, uint64_t NumClients) :
        Index_(Index),
        SerialStart_(std::move(SerialStart)),
        NumClients_(NumClients)
    {

    }

    void run() override;
    void stop() { Stop_ = true; }
    void Initialize();

private:
    static Simulator * instance_;
    std::mutex mutex_;
    Poco::Net::SocketReactor                                Reactor_;
    std::map<std::string,std::shared_ptr<uCentralClient>>   Clients_;
    Poco::Thread                                            SocketReactorThread_;
    volatile bool                                           Stop_ = false;
    uint64_t                                                Index_;
    std::string                                             SerialStart_;
    uint64_t                                                NumClients_;
};


#endif //UCENTRAL_CLNT_SIMULATOR_H
