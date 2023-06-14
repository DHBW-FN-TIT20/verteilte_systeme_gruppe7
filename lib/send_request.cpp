/**************************************************************************************************
 * @file    send_request.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    10-June-2023
 * @brief   This file contains the implementation for the two global functions sendRequest and
 *          sendRequestWithoutResponse and the helper function splitAndRemoveNewLine which manage
 *          the request sending process to the server and handle the response.
 *          In case of an error the program is terminated with a suitable exception.
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "send_request.h"

/**************************************************************************************************
 * Public - Function implementation
 *************************************************************************************************/

std::vector<std::string> network::splitAndRemoveNewline(std::string str) {
  /* remove \n from end of the string if it exists */
  if(!str.empty() && str[str.length() - 1] == '\n') {
    str.erase(str.length() - 1);
  }

  /* split the string at the delimiter ";" */
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string item;

  while(std::getline(ss, item, ';')) {
    result.push_back(item);
  }

  return result;
}

void network::sendRequestWithoutResponse(std::shared_ptr<TcpClient> client, RequestType &request) {
  MessageParser messageParser;
  LogManager logger(LOG_FILE_NAME);

  std::string requestStr = messageParser.encodeObject(request);
  std::string clientEndpointStr = client->socket().local_endpoint().address().to_string() + ":" + std::to_string(client->socket().local_endpoint().port());

  /* send request to server */
  client->sendMessage(requestStr);
  std::string responseStr = client->waitForSingleResponse();    //get action status
  std::vector<std::string> responseSubStr = splitAndRemoveNewline(responseStr);    //remove "\n" from reponse
  ActionStatusType actionStatus = messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0));

  if(responseSubStr.size() == 1 && actionStatus == ActionStatusType::STATUS_OK) {
    logger.addLogEntry("Client on " + clientEndpointStr + " " + request.mAction.toString() + " successful");
    return;
  }
  //std::cout << logger.getTimestampString() << actionStatus.toString() << std::endl;
  logger.addLogEntry("Client on " + clientEndpointStr + ": received action status >>" + actionStatus.toString() + "<<");
  throw std::runtime_error("Action status: " + actionStatus.toString());
}

