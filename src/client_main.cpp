/**************************************************************************************************
 * @file    subscriber_main.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    07-June-2023
 * @brief   
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <algorithm>
#include "subscriber.h"

/**************************************************************************************************
 * Public - Global variables
 *************************************************************************************************/
Subscriber* Subscriber::instance = nullptr;

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

  /* get action */
  it = std::find(args.begin(), args.end(), "--action");
  if(it != args.end() && ++it != args.end()) {
    std::string action = *it;
    if(action == "SUBSCRIBE_TOPIC") {
      it = std::find(args.begin(), args.end(), "--topicName");
      if(it != args.end() && ++it != args.end()) {
        Subscriber subscriber(serverEndpoint);
        subscriber.subscribeTopic(*it);
      } else {
        throw std::invalid_argument("No topic name found");
      }
    } else if(action == "LIST_TOPICS") {
      Subscriber subscriber(serverEndpoint);
      subscriber.listTopics();
    } else if(action == "PUBLISH_TOPIC") {
      it = std::find(args.begin(), args.end(), "--topicName");
      if(it != args.end() && ++it != args.end()) {
        std::string topicName = *it;
        it = std::find(args.begin(), args.end(), "--message");
        if(it != args.end() && ++it != args.end()) {
          //Publisher publisher(serverEndpoint);
          //publisher.publishTopic(topicName, *it);
        } else {
          throw std::invalid_argument("No message found");
        }
      } else {
        throw std::invalid_argument("No topic name found");
      }
    } else if(action == "GET_TOPIC_STATUS") {
      it = std::find(args.begin(), args.end(), "--topicName");
      if(it != args.end() && ++it != args.end()) {
        //Publisher publisher(serverEndpoint);
        //publisher.getTopicStatus(*it);
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
