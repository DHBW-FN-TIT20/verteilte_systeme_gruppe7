/**************************************************************************************************
  * @file    subscriber.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    10-June-2023
  * @brief   Prototype for class Subscriber
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <iostream>
#include <iomanip>
#include <csignal>

/* Own Libs / datatypes */
#include "action_type.h"
#include "action_status_type.h"
#include "defines.h"
#include "endpoint_type.h"
#include "request_type.h"
#include "topic_name_list_type.h"

#include "tcp/tcp_client.hpp"
#include "log_manager.h"
#include "parser/message_parser.hpp"
#include "send_request.h"

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class Subscriber {
  private:
    T_Endpoint                      mServerEndpoint;
    T_Endpoint                      mOwnEndpoint;
    MessageParser                   mMessageParser;
    LogManager                      mLogger;
    std::shared_ptr<TcpClient>      mTcpClient;
    std::string                     mTopicName;

  protected:
    /**
     * @brief Unsubscribe subscriber from the topic.
     * If no more subscribers are registered on this topic, it will be deleted.
     * 
     * @param topicName Topic name
     */
    void unsubscribeTopic(const std::string &topicName);

  public:
    static Subscriber* instance;
    
    Subscriber(const T_Endpoint &endpoint, std::function<void(const std::string)> callback);

    /**
     * @brief Default destructor for class Subscriber
     * 
     */
    ~Subscriber();

    /**
     * @brief Register subscriber to the topic.
     * 
     * @param topicName Topic name
     */
    void subscribeTopic(const std::string &topicName);

    /**
     * @brief List all topics that currently exist in the broker
     * 
     */
    T_TopicNameList listTopics(void);

    /**
     * @brief catch and handle OS signals
     * 
     * @param signum signal number
     */
    static void signalHandler(int signum);
};
