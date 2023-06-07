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
#include <memory>
#include <chrono>
#include <ctime>

/* Own Libs / datatypes */
#include "topic_list_type.h"
#include "topic_status_type.h"
#include "tcp/tcp_server.hpp"

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/
class Broker{
  private:
    T_TopicList mTopicList;

  protected:
    /**
     * @brief Add subscriber to subscriber list of the given topic
     * 
     * @param topicName 
     * @return ActionStatusType 
     */
    ActionStatusType subscribeTopic(std::string topicName);

    /**
     * @brief Delete subscriber from subscriber list of the giben topic.
     * If subscriber list is empty after that, delete the topic.
     * 
     * @param topicName Topic to unsubscribe from
     * @return ActionStatusType Action status
     */
    ActionStatusType unsubscribeTopic(std::string topicName);

    /**
     * @brief Publish a topic with the given message
     * 
     * @param topicName Topic to publish on
     * @param message Message to publish
     * @return ActionStatusType Action status
     */
    ActionStatusType publishTopic(std::string topicName, std::string &message);

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
    T_TopicStatus getTopicStatus(std::string topicName) const;

    /**
     * @brief Update the topic by sending it to all subscribers of the topic with the given message and timestamp
     * 
     * @param topicName Topic to update
     * @param message Message to send
     * @param timestamp Timestamp of the current topic update
     */
    void updateTopic(std::string topicName, std::string &message, std::time_t timestamp);


  public:
    /**
     * @brief Default constructor for class Broker
     * 
     */
    Broker(void);

    /**
     * @brief Construct a new Broker object with an initial topic list.
     * This constructor is used for unit tests.
     * 
     * @param topicList Initial topic list
     */
    Broker(const T_TopicList& topicList);

    /**
     * @brief Handle incoming messages from clients
     * 
     * @param conn Tcp connection to client
     * @param message Message from client
     */
    void messageHandler(std::shared_ptr<TcpConnection> conn, const std::string message);
};
