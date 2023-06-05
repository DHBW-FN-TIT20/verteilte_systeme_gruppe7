/**************************************************************************************************
 * @file    publisher.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   Prototype for class Publisher
 **************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>

/* Own Libs / datatypes */
#include "topic_status_type.h"
#include "request_type.h"

/*************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class Publisher {
  protected:
    /**
     * @brief Send specified request to the broker
     *
     * @param request The request which should be send to the broker
     */
    virtual std::string sendRequest(const RequestType &request) const;

  public:
    /**
     * @brief Publish new information on a topic
     * 
     * @param topicName Topic name where the message should be published to
     * @param msg The message which should be published
     */
    void publishTopic(const std::string topicName, const std::string &message) const;
    /**
     * @brief Get info about the specified topic
     *
     * @param topicName Topic name for which information is requested
     */
    void getTopicStatus(const std::string topicName) const;
};
