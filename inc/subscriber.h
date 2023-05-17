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
typedef vector<SUBSCRIBER>              T_subscriber_list;
typedef map<string, T_subscriber_list>  T_topic_list;

typedef struct {
  bool              is_topic_available;
  int32_t           timestamp;
  T_subscriber_list subscriber_list_t;
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
    bool subscribe_topic(string topic) const;

    /**
     * @brief Unsubscribe subscriber from the topic.
     * If no more subscribers are registered on this topic, it will be deleted.
     * 
     * @param topic Topic name
     * @return true 
     * @return false 
     */
    bool unsubscribe_topic(string topic) const;

    /**
     * @brief Publish new information on a topic
     * 
     * @param topic Topic name
     * @param msg Message to publish
     * @return true Topic updated successfully
     * @return false Error: Topic doesn't exist / invalid parameters
     */
    bool publish_topic(string topic, string &msg) const;

    /**
     * @brief Request list of available topics.
     * 
     * @return vector<string>* Pointer to list of topics
     */
    vector<string>* list_topics(void) const;

    /**
     * @brief Get the topic status object
     * 
     * @param topic Topic name
     * @return TOPIC_STATUS Current status of the topic
     */
    TOPIC_STATUS get_topic_status(string topic) const;

    /**
     * @brief Send the content of a topic to all subscribers.
     * 
     * @param topic Topic name
     * @param msg Message
     * @param timestamp timestamp of latest update
     */
    void update_topic(string topic, string &msg, int32_t timestamp) const;

};
