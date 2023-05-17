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
#include "./main.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef vector<SUBSCRIBER>              T_SubscriberList;
typedef map<string, T_SubscriberList>   T_TopicList;

typedef struct {
  bool                                  IsTopicAvailable;
  int32_t                               Timestamp;
  T_SubscriberList                      SubscriberList_t;
} TOPIC_STATUS;

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class SUBSCRIBER {
  private:
  

  public:
    /**
     * @brief Register subscriber to the topic. If it doesn't exist, it will be created.
     * 
     * @param topic Topic name
     * @return true Subscriber registered successfully
     * @return false Error: invalid parameters
     */
    bool subscribeTopic(string topic) const;

    /**
     * @brief Unsubscribe subscriber from the topic.
     * If no more subscribers are registered on this topic, it will be deleted.
     * 
     * @param topic Topic name
     * @return true 
     * @return false 
     */
    bool unsubscribeTopic(string topic) const;

    /**
     * @brief Publish new information on a topic
     * 
     * @param topic Topic name
     * @param msg Message to publish
     * @return true Topic updated successfully
     * @return false Error: Topic doesn't exist / invalid parameters
     */
    bool publishTopic(string topic, string &msg) const;

    /**
     * @brief Request list of available topics.
     * 
     * @return vector<string>* Pointer to list of topics
     */
    vector<string>* listTopics(void) const;

    /**
     * @brief Get the topic status object
     * 
     * @param topic Topic name
     * @return TOPIC_STATUS Current status of the topic
     */
    TOPIC_STATUS getTopicStatus(string topic) const;

    /**
     * @brief Send the content of a topic to all subscribers.
     * 
     * @param topic Topic name
     * @param msg Message
     * @param timestamp timestamp of latest update
     */
    void updateTopic(string topic, string &msg, int32_t timestamp) const;

};
