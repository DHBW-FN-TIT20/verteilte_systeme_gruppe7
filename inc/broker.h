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

/* Own Libs / datatypes */
#include "topic_list_type.h"
#include "topic_status_type.h"
#include "subscriber_list_type.h"
#include "tcp/tcp_server.hpp"

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/
class Broker{
  protected:
    T_TopicList mTopicList;
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
    bool hasSubscriber(const std::string &topicName, const T_Endpoint &subscriber) const;

    /**
     * @brief Add subscriber to subscriber list of the given topic
     * 
     * @param topicName 
     * @return ActionStatusType 
     */
    ActionStatusType subscribeTopic(const std::string &topicName, const T_Endpoint &subscriber);

    /**
     * @brief Delete subscriber from subscriber list of the giben topic.
     * If subscriber list is empty after that, delete the topic.
     * 
     * @param topicName Topic to unsubscribe from
     * @return ActionStatusType Action status
     */
    ActionStatusType unsubscribeTopic(const std::string &topicName, const T_Endpoint &subscriber);

    /**
     * @brief Publish a topic with the given message
     * 
     * @param topicName Topic to publish on
     * @param message Message to publish
     * @return ActionStatusType Action status
     */
    ActionStatusType publishTopic(const std::string &topicName, const std::string &message) const;

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
     * @brief Update the topic by sending it to all subscribers of the topic with the given message and timestamp
     * 
     * @param topicName Topic to update
     * @param message Message to send
     * @param timestamp Timestamp of the current topic update
     */
    void updateTopic(const std::string &topicName, const std::string &message, const std::time_t &timestamp) const;


  public:
    /**
     * @brief Default constructor for class Broker
     * 
     */
    Broker(void);

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
};
