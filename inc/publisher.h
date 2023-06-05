/**
 *************************************************************************************************
 * @file    publisher.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   
 *************************************************************************************************
 */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>

/* Own Libs / datatypes */
#include "topic_status_type.h"

using std::string;

 /*************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class PUBLISHER {
  private:
  

  public:
    /**
     * @brief Publish new information on a topic
     * 
     * @param topic Topic name
     * @param msg Message to publish
     * @return true Topic updated successfully
     * @return false Error: Topic doesn't exist / invalid parameters
     */
    bool publishTopic(const string topicName, const string &msg) const;

    /**
     * @brief Get the topic status object
     * 
     * @param topic Topic name
     * @return TOPIC_STATUS Current status of the topic
     */
    T_TopicStatus getTopicStatus(const string topicName) const;

};
