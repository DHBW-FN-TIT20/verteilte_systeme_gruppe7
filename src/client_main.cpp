/**************************************************************************************************
 * @file    client_main.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    17-June-2023
 * @brief   This file contains the program entry point and instantiation of a subscriber / publisher object
 *          -> Main file for clients (subscriber / publisher)
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <algorithm>
#include "subscriber.h"
#include "publisher.h"

/**************************************************************************************************
 * Public - Global variables
 *************************************************************************************************/
Subscriber* Subscriber::instance = nullptr;
Publisher* Publisher::instance = nullptr;

void messageHandler(const std::string message);

/**************************************************************************************************
 * Program entry point
 *************************************************************************************************/
int main(int argc, char* argv[]) {
  std::vector<std::string> args(argv, argv + argc);
  T_Endpoint serverEndpoint;

  /* get server endpoint */
  auto it = std::find(args.begin(), args.end(), "--server-address");
  if(it != args.end() && ++it != args.end()) {
    serverEndpoint.address = *it;
    it = std::find(args.begin(), args.end(), "--server-port");
    if(it != args.end() && ++it != args.end()) {
      serverEndpoint.port = *it;
    } else {
      throw std::invalid_argument("No server-port found");
    }
  } else {
    throw std::invalid_argument("No server-address found");
  }

  /* get action and execute it */
  it = std::find(args.begin(), args.end(), "--action");
  if(it != args.end() && ++it != args.end()) {
    std::string action = *it;
    if(action == "SUBSCRIBE_TOPIC") {
      it = std::find(args.begin(), args.end(), "--topic-name");
      if(it != args.end() && ++it != args.end()) {
        Subscriber subscriber(serverEndpoint, messageHandler);
        subscriber.subscribeTopic(*it);
      } else {
        throw std::invalid_argument("No topic name found");
      }
    } else if(action == "LIST_TOPICS") {
      Subscriber subscriber(serverEndpoint, messageHandler);
      if(T_TopicNameList topicList = subscriber.listTopics(); topicList.TopicNameList.size() > 0) {
        std::cout << "Existing topics:" << std::endl;
        for(auto& topic : topicList.TopicNameList) {
          std::cout << "- " << topic << std::endl;
        }
        std::cout << std::endl;
      } else {
        std::cout << "No topics exist. You can publish one and try again." << std::endl;
      }
    } else if(action == "PUBLISH_TOPIC") {
      it = std::find(args.begin(), args.end(), "--topic-name");
      if(it != args.end() && ++it != args.end()) {
        std::string topicName = *it;
        it = std::find(args.begin(), args.end(), "--message");
        if(it != args.end() && ++it != args.end()) {
          Publisher publisher(serverEndpoint);
          publisher.publishTopic(topicName, *it);
          std::cout << "Successfully published message on topic >>" << topicName << "<<" << std::endl;
        } else {
          throw std::invalid_argument("No message found");
        }
      } else {
        throw std::invalid_argument("No topic name found");
      }
    } else if(action == "GET_TOPIC_STATUS") {
      it = std::find(args.begin(), args.end(), "--topic-name");
      if(it != args.end() && ++it != args.end()) {
        Publisher publisher(serverEndpoint);
        T_TopicStatus topicStatus = publisher.getTopicStatus(*it);
        std::cout << "Status of " << *it << ": " << topicStatus.toString() << std::endl;
      } else {
        throw std::invalid_argument("No topic name found");
      }
    } else {
      throw std::invalid_argument("Action invalid\n\nOptions are:\n> SUBSCRIBE_TOPIC\n> LIST_TOPICS\n> PUBLISH_TOPIC\n> GET_TOPIC_STATUS\n");
    }
  } else {
    throw std::invalid_argument("No action found");
  }


  return 0;
}

/**************************************************************************************************
 * Public - function implementation
 *************************************************************************************************/
void messageHandler(const std::string message) {
  MessageParser parser;
  LogManager logger(LOG_FILE_NAME);

  /* parse message */
  RequestType request = parser.decodeObject<RequestType>(message);

  /* extract relevant information from response */
  const std::string topicName = request.mParameterList.at("topicName");
  const std::string topicMessage = request.mParameterList.at("message");
  std::time_t topicTimestamp = request.mTimestamp;

  std::cout << std::endl << logger.getTimestampString() << "received topic >>" << topicName << "<<" << std::endl;
  std::cout << "> Topic message: " << topicMessage << std::endl;
  std::cout << "> Timestamp: " << topicTimestamp << std::endl << std::endl;
}
