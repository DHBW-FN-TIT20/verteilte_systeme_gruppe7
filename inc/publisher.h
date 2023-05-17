/**
 *************************************************************************************************
 * @file    publisher.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    17-May-2023
 * @brief   
 *************************************************************************************************
 */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "./main.h"


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
    bool publishTopic(string topic, string &msg) const;

    /**
     * @brief Get the topic status object
     * 
     * @param topic Topic name
     * @return TOPIC_STATUS Current status of the topic
     */
    TOPIC_STATUS getTopicStatus(string topic) const;

};
