/**
  *************************************************************************************************
  * @file    subscriber.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    29-May-2023
  * @brief   Prototype for class Subscriber
  *************************************************************************************************
  */

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
#include "topic_status_type.h"


/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class Subscriber {
  protected:
    /**
     * @brief Register subscriber to the topic. If it doesn't exist, it will be created.
     * 
     * @param topicName Topic name
     * @return true Subscriber registered successfully
     * @return false Error: invalid parameters
     */
    bool subscribeTopic(std::string topicName) const;

    /**
     * @brief Unsubscribe subscriber from the topic.
     * If no more subscribers are registered on this topic, it will be deleted.
     * 
     * @param topicName Topic name
     * @return true 
     * @return false 
     */
    bool unsubscribeTopic(std::string topicName) const;

    /**
     * @brief Publish new information on a topic
     * 
     * @param topicName Topic name
     * @param msg Message to publish
     * @return true Topic updated successfully
     * @return false Error: Topic doesn't exist / invalid parameters
     */
    bool publishTopic(std::string topicName, std::string &msg) const;

    /**
     * @brief Get the topic status object
     * 
     * @param topicName Topic name
     * @return TOPIC_STATUS Current status of the topic
     */
    T_TopicStatus getTopicStatus(std::string topicName) const;

    /**
     * @brief Send the content of a topic to all subscribers.
     * 
     * @param topicName Topic name
     * @param msg Message
     * @param timestamp timestamp of latest update
     */
    void updateTopic(std::string topicName, std::string &msg, std::time_t timestamp);

    /**
     * @brief Send a request to the broker via TCP
     * 
     * @param request Request to be sent to the broker
     * @return int 0: successfully sent
     *            >0: error
     */
    //std::string sendRequest(const RequestType& request) const;

  public:
    
    Subscriber(std::string address, int port);

    /**
     * @brief Default destructor for class Subscriber
     * 
     */
    ~Subscriber();

};
