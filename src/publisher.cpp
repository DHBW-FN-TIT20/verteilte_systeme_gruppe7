/**
 *************************************************************************************************
 * @file    publisher.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    31-May-2023
 * @brief   Implements the publisher file 
 *************************************************************************************************
 */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "publisher.h"

using namespace std;

string PUBLISHER::sendRequest(const RequestType &request) const {
  return "";
}

void PUBLISHER::publishTopic(const string topicName, const string &message) const {
  // create message object
  map<string, string> requestParameters;
  requestParameters.insert({"message", message});

  const RequestType request = {
    ACTION_ENUM::GET_TOPIC_STATUS,
    requestParameters,
    12345678 // dummy timestamp
  };

  // send request
  const string responeMessage = sendRequest(request);

  // parse response
  // (parse string to action_status_enum)
}
