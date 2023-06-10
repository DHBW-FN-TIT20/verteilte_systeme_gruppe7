/**************************************************************************************************
  * @file    subscriber.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    10-June-2023
  * @brief   Prototype for class Subscriber
  ************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <iomanip>

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

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class Subscriber {
  private:
  T_Endpoint                      mServerEndpoint;
  MessageParser                   mMessageParser;
  LogManager                      mLogger;
  std::shared_ptr<TcpClient>      mTcpClient;
  protected:

    /**
     * @brief Unsubscribe subscriber from the topic.
     * If no more subscribers are registered on this topic, it will be deleted.
     * 
     * @param topicName Topic name
     */
    void unsubscribeTopic(const std::string &topicName) const;

    /**
     * @brief Send the content of a topic to all subscribers.
     * 
     * @param topicName Topic name
     * @param msg Message
     * @param timestamp timestamp of latest update
     */
    void updateTopic(const std::string &topicName, const std::string &msg, const std::time_t &timestamp) const;

  public:
    static Subscriber* instance;
    
    Subscriber(const std::string &address, const std::string &port);

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
    void listTopics(void);

    /**
     * @brief handle incoming messages during continuous receive
     * 
     * @param message response from server
     */
    void messageHandler(const std::string message) const;

    /**
     * @brief catch and handle OS signals
     * 
     * @param signum signal number
     */
    void signalHandler(int signum);

};
