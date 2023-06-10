/**************************************************************************************************
 * @file    broker.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    07-June-2023
 * @brief   Prototype for class Broker
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <mutex>
#include <csignal>

/* Own Libs / datatypes */
#include "topic_type.h"
#include "topic_list_type.h"
#include "topic_status_type.h"
#include "subscriber_type.h"
#include "subscriber_list_type.h"
#include "endpoint_type.h"
#include "request_type.h"
#include "defines.h"

#include "log_manager.h"
#include "parser/message_parser.hpp"
#include "tcp/tcp_server.hpp"

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/
class Broker{
  protected:
    T_TopicList mTopicList;
    T_Endpoint mOwnEndpoint;
    LogManager mLogger;
    MessageParser mMessageParser;
    TcpServer brokerTcpServer;
    mutable std::mutex mTopicListMutex;

    /**
     * @brief Check if a specific topic exists in the topic list.
     * ! Invoke only when mutex is locked !
     * 
     * @param topicName Topic of which existence is to be checked
     * @return true Topic is in list
     * @return false Topic is not in list
     */
    bool isTopicExistent(const std::string &topicName) const;

    /**
     * @brief Check if a specific subscriber is in the subscriber list of a specific topic in the topic list
     * ! invoke only when mutex is locked !
     * 
     * @param topicName Topic of which to check subscriber list for subscriber
     * @param subscriber Subscriber whose existence in the subscriber list is to be checked
     * @return true Subscriber exists in the subscriber list of the given topic
     * @return false Subscriber does not exist in the subscriber list of the given topic
     */
    bool hasSubscriber(const std::string &topicName, const T_Subscriber &subscriber) const;

    /**
     * @brief Add subscriber to subscriber list of the given topic
     * 
     * @param topicName 
     * @return ActionStatusType 
     */
    ActionStatusType subscribeTopic(const std::string &topicName, const T_Subscriber &subscriber);

    /**
     * @brief Delete subscriber from subscriber list of the giben topic.
     * If subscriber list is empty after that, delete the topic.
     * 
     * @param topicName Topic to unsubscribe from
     * @return ActionStatusType Action status
     */
    ActionStatusType unsubscribeTopic(const std::string &topicName, const T_Subscriber &subscriber);

    /**
     * @brief Publish a topic with the message specified in the request. Update the request and forward it to the subscribers.
     * Update the latest request of the topic in the topic list with the new request from the publisher.
     * If the topic doesn't exist, it will be created.
     * 
     * @param requestFromPublisher
     * @return ActionStatusType Action status
     */
    ActionStatusType publishTopic(RequestType &requestFromPublisher);

    /**
     * @brief Get a list of all existing topics
     * 
     * @return T_TopicList List of all topics
     */
    std::vector<std::string> listTopics(void) const;

    /**
     * @brief Get the status of the given topic
     * 
     * @param topicName Topic to get status from
     * @return T_TopicStatus Status of the topic
     */
    T_TopicStatus getTopicStatus(const std::string &topicName) const;

    /**
     * @brief Update the topic by sending it to all subscribers of the topic specified in the request
     * 
     * @param requestToSubscriber Request to be sent to all subscribers of the topis
     */
    void updateTopic(RequestType &requestToSubscriber);


  public:
    static Broker* instance;
    
    /**
     * @brief No default constructor for class Broker
     * 
     */
    Broker(void);

    /**
     * @brief Default constructor for class Broker
     * 
     * @param address IPv4 address of the Broker
     * @param port Port the broker will listen on
     */
    Broker(const std::string address, const std::string port);

    /**
     * @brief Default destructor for class Broker
     * 
     */
    ~Broker(void);

    /**
     * @brief Handle incoming messages from clients
     * 
     * @param conn Tcp connection to client
     * @param message Message from client
     */
    void messageHandler(std::shared_ptr<TcpConnection> conn, const std::string message);

    /**
     * @brief 
     * 
     * @param signum 
     */
    static void signalHandler(int signum);
};
