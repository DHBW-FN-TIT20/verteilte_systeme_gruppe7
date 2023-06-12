/**************************************************************************************************
 * @file    send_request.hpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    10-June-2023
 * @brief   This file contains the declaration for the two global functions sendRequest and
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
#include "defines.h"

#include "parser/message_parser.hpp"
#include "log_manager.h"
#include "tcp/tcp_client.hpp"

/**************************************************************************************************
 * Public - Function prototypes
 *************************************************************************************************/
namespace network {
  /**
   * @brief Split a string at ";" and remove trailing newline
   * 
   * @param str string to split
   * @return std::vector<std::string> splitted substrings
   */
  std::vector<std::string> splitAndRemoveNewline(std::string str);

  /**
   * @brief Send a request to the TCP server and return the response
   * Invoke only with the following action types:
   * > LIST_TOPICS
   * > GET_TOPIC_STATUS
   * 
   * @param client Open connection to the server
   * @param request Request to be sent to the server
   * @return T Type to parse response into. Provided by the caller function.
   */
  template<typename T>
  T sendRequest(std::shared_ptr<TcpClient> client, RequestType &request) {
    MessageParser messageParser;
    LogManager logger("log.txt");

    /* send request to server */
    client->sendMessage(messageParser.encodeObject(request));
    std::string clientEndpointStr = client->socket().local_endpoint().address().to_string() + ":" + std::to_string(client->socket().local_endpoint().port());


    /* handle response from server */
    std::string responseStr = client->waitForSingleResponse();    //read single action status
    std::vector<std::string> responseSubStr = splitAndRemoveNewline(responseStr);    //remove "\n" from resonse and split it at ";"
    ActionStatusType actionStatus = messageParser.decodeObject<ActionStatusType>(responseSubStr.at(0));

    if(responseSubStr.size() > 1 && actionStatus == ActionStatusType::STATUS_OK) {
      T result = messageParser.decodeObject<T>(responseSubStr.at(1));
      logger.addLogEntry("Client on " + clientEndpointStr + " " + request.mAction.toString() + " successful; Response: >>" + result.toString() + "<<");
      return result;
    }
    //std::cout << logger.getTimestampString() << actionStatus.toString() << std::endl;
    logger.addLogEntry("Client on " + clientEndpointStr + ": received action status >>" + actionStatus.toString() + "<<");
    throw std::runtime_error("Action status: " + actionStatus.toString());
  }

  /**
   * @brief Send a request to the TCP server. Only expect an action status as response and handle it.
   * Invoke only with the following action types:
   * > SUBSCRIBE_TOPIC
   * > UNSUBSCRIBE_TOPIC
   * > PUBLISH_TOPIC
   * 
   * @param client Open connection to the server
   * @param request Request to be sent to the server
   */
  void sendRequestWithoutResponse(std::shared_ptr<TcpClient> client, RequestType &request);
}