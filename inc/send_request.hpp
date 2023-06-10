/**************************************************************************************************
 * @file    send_request.hpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    10-June-2023
 * @brief   This file contains the implementation for the two global functions sendRequest and
 *          sendRequestWithoutResponse and the helper function splitAndRemoveNewLine which manage
 *          the request sending process to the server and handle the response.
 *          In case of an error the program is terminated with a suitable exception.
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>


/* Own Libs / datatypes */
#include "request_type.h"
#include "action_type.h"
#include "action_status_type.h"
#include "topic_status_type.h"
#include "topic_name_list_type.h"

#include "parser/message_parser.hpp"
#include "log_manager.h"
#include "tcp/tcp_client.hpp"

/**************************************************************************************************
 * Public - Function implementation
 *************************************************************************************************/
std::vector<std::string> splitAndRemoveNewline(std::string str) {
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



/**
 * @brief Send a request to the TCP server and return the response
 * 
 * @param client Open connection to the server
 * @param request Request to be sent to the server
 * @return T Type to parse response into. Provided by the caller function.
 */
template<typename T>
T sendRequest(std::shared_ptr<TcpClient> client, RequestType &request) {
  MessageParser messageParser;
  LogManager logger("log.txt");

  std::string clientEndpointStr = client->socket().local_endpoint().address().to_string() + ":" + std::to_string(client->socket().local_endpoint().port());
  std::string responseStr;
  std::vector<std::string> responseSubStr;
  T result;

  /* send request to server */
  client->sendMessage(messageParser.encodeObject(request));


  /* handle response from server */
  switch(request.mAction) {
    case ActionType::LIST_TOPICS:
    case ActionType::GET_TOPIC_STATUS:
      responseStr = client->waitForSingleResponse();    //read single action status
      responseSubStr = splitAndRemoveNewline(responseStr);    //remove "\n" from resonse and split it at ";"
      if(responseSubStr.size() > 1) {   //at least 2 elements were in the response
        if(messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)) == ActionStatusType::STATUS_OK) {   //no error -> response is complete
          logger.addLogEntry(clientEndpointStr + ">>" + result.toString() + "<<");
          result = messageParser.decodeObject<T>(responseSubStr.at(1));
          return result;
        } else {
          std::cout << logger.getTimestampString() << messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)).toString() << std::endl;
          logger.addLogEntry(clientEndpointStr + " " + ">>" + messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)).toString()) + "<<";
          throw std::runtime_error("Action status: " + messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)).toString());
        }
      } else {
        std::cout << logger.getTimestampString() << "INVALID_PARAMETERS" << std::endl;
        logger.addLogEntry(clientEndpointStr + " >>INVALID_PARAMETERS<<");
        throw std::runtime_error("INVALID_PARAMETERS");
      }
      break;
    default:
      logger.addLogEntry(clientEndpointStr + " >>INTERNAL_ERROR<<");
      throw std::runtime_error("INTERNAL_ERROR");
      break;
  }
}


/**
 * @brief Send a request to the TCP server. Only expect an action status as response and handle it.
 * 
 * @param client Open connection to the server
 * @param request Request to be sent to the server
 */
void sendRequestWithoutResponse(std::shared_ptr<TcpClient> client, RequestType &request) {
  MessageParser messageParser;
  LogManager logger("log.txt");

  std::string requestStr = messageParser.encodeObject(request);
  std::string responseStr, errorStr;
  std::vector<std::string> responseSubStr;
  std::string clientEndpointStr = client->socket().local_endpoint().address().to_string() + ":" + std::to_string(client->socket().local_endpoint().port());

  /* send request to server */
  client->sendMessage(requestStr);
  responseStr = client->waitForSingleResponse();    //get action status

  switch(request.mAction) {
    case ActionType::SUBSCRIBE_TOPIC:
    case ActionType::UNSUBSCRIBE_TOPIC:
    case ActionType::PUBLISH_TOPIC:
      responseSubStr = splitAndRemoveNewline(responseStr);    //remove "\n" from reponse
      if(responseSubStr.size() == 1) {
        if(messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)) == ActionStatusType::STATUS_OK) {
          std::cout << logger.getTimestampString() << request.mAction.toString() << " successful" << std::endl;
          logger.addLogEntry(clientEndpointStr + " " + request.mAction.toString() + " successful");
        } else {
          std::cout << logger.getTimestampString() << messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)).toString() << std::endl;
          logger.addLogEntry(clientEndpointStr + " " + ">>" + messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)).toString() + "<<");
          throw std::runtime_error("Action status: " + messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0)).toString());
        }
      } else {
        std::cout << logger.getTimestampString() << "INVALID_PARAMETERS" << std::endl;
        logger.addLogEntry(clientEndpointStr + " >>INVALID_PARAMETERS<<");
        throw std::runtime_error("INVALID_PARAMETERS");
      }
    default:
      logger.addLogEntry(clientEndpointStr + " >>INTERNAL_ERROR<<");
      throw std::runtime_error("INTERNAL_ERROR");
      break;
  }
}
