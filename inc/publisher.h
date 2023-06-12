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
#include "defines.h"

#include "tcp/tcp_client.hpp"
#include "log_manager.h"

/*************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/
class Publisher {
  private:
    T_Endpoint                  mOwnEndpoint;
    LogManager                  mLogger;
    std::shared_ptr<TcpClient>  mTcpClient;

  public:
    static Publisher* instance;

    /**
     * @brief Default constructor for class Publisher
     *
     */
    Publisher(const T_Endpoint &endpoint);

    /**
     * @brief No default constructor for class Publisher
     *
     */
    Publisher(void);

    /**
     * @brief Default destructor for class Publisher
     *  
     */
    ~Publisher(void);

    /**
     * @brief Publish new information on a topic
     * 
     * @param topicName Topic name where the message should be published to
     * @param msg The message which should be published
     */
    void publishTopic(const std::string topicName, const std::string &message);

    /**
     * @brief Get info about the specified topic
     *
     * @param topicName Topic name for which information is requested
     */
    T_TopicStatus getTopicStatus(const std::string topicName);

    /**
     * @brief Handles OS signales
     *
     * @param signalNumber signal number
     */
    static void signalHandler(int signalNumber);
};
