/**************************************************************************************************
 * @file    publisher.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   Implementation for class Publisher
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "publisher.h"

using namespace std;

/**************************************************************************************************
 * Public - Class implementation
 *************************************************************************************************/
string Publisher::sendRequest(const RequestType &request) const {
  return "";
}

void Publisher::publishTopic(const string topicName, const string &message) const {
  // create message object
  map<string, string> requestParameters = {
    {"topicName", topicName},
    {"message", message}
  };

  const RequestType request = RequestType(ActionType::PUBLISH_TOPIC, requestParameters);

  // send request
  const string responeMessage = sendRequest(request);
}

void Publisher::getTopicStatus(const string topicName) const {
  map<string, string> requestParameters = {
    {"topicName", topicName}
  };

  const RequestType request = RequestType(ActionType::GET_TOPIC_STATUS, requestParameters);

  // send request
  sendRequest(request);
}
