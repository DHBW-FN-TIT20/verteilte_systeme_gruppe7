/**************************************************************************************************
 * @file    subscriber_main.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    07-June-2023
 * @brief   
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <any>
#include "subscriber.h"
#include "endpoint_type.h"
#include "send_request.hpp"


/**************************************************************************************************
 * Program entry point
 *************************************************************************************************/
void messageHandler(std::string message) {
  std::cout << message << std::endl;
}

int main() {
  RequestType pubRequest = {
    ActionType::PUBLISH_TOPIC,
    {{"topicName", "secondTopic"}, {"message", "another message"}}
  };



  RequestType listRequest = {
    ActionType::LIST_TOPICS,
    {}
  };



  RequestType subRequest = {
    ActionType::SUBSCRIBE_TOPIC,
    {{"topicName", "secondTopic"}}
  };



  RequestType getRequest = {
    ActionType::GET_TOPIC_STATUS,
    {{"topicName", "secondTopic"}}
  };



  auto client = std::make_shared<TcpClient>(T_Endpoint{"localhost", "8080"}, messageHandler);
  client->connect();

  //std::vector<std::string> topicList = std::any_cast<std::vector<std::string>>(sendRequest(client, request));
  //int status = std::any_cast<int>(sendRequest(client, request));
  T_TopicStatus topicStatus = sendRequest<T_TopicStatus>(client, getRequest);
  T_TopicNameList topicNames = sendRequest<T_TopicNameList>(client, listRequest);
  //(void)sendRequest<void>(client, pubRequest);



  std::cout << topicStatus.toString() << std::endl;

  client->run();
  client->close();
  
  return 0;
}
