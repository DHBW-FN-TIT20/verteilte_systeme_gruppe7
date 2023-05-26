/**
  *************************************************************************************************
  * @file    subscriber.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    16-May-2023
  * @brief   
  *************************************************************************************************
  */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>
#include <vector>

/* Own Libs / datatypes */
#include "T_TopicStatus.h"

using std::string;
using std::vector;

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class SUBSCRIBER {
  private:
    /**
     * @brief Register subscriber to the topic. If it doesn't exist, it will be created.
     * 
     * @param topicName Topic name
     * @return true Subscriber registered successfully
     * @return false Error: invalid parameters
     */
    bool subscribeTopic(string topicName) const;

    /**
     * @brief Unsubscribe subscriber from the topic.
     * If no more subscribers are registered on this topic, it will be deleted.
     * 
     * @param topicName Topic name
     * @return true 
     * @return false 
     */
    bool unsubscribeTopic(string topicName) const;

    /**
     * @brief Publish new information on a topic
     * 
     * @param topicName Topic name
     * @param msg Message to publish
     * @return true Topic updated successfully
     * @return false Error: Topic doesn't exist / invalid parameters
     */
    bool publishTopic(string topicName, string &msg) const;

    /**
     * @brief Request list of available topics.
     * 
     * @return vector<string>* Pointer to list of topics
     */
    vector<string>* listTopics(void) const;

    /**
     * @brief Get the topic status object
     * 
     * @param topicName Topic name
     * @return TOPIC_STATUS Current status of the topic
     */
    T_TopicStatus getTopicStatus(string topicName) const;

    /**
     * @brief Send the content of a topic to all subscribers.
     * 
     * @param topicName Topic name
     * @param msg Message
     * @param timestamp timestamp of latest update
     */
    void updateTopic(string topicName, string &msg, int32_t timestamp) const;

  public:
    
    SUBSCRIBER(string address, int port);

    /**
     * @brief Default destructor for class SUBSCRIBER
     * 
     */
    ~SUBSCRIBER();

};
