/**************************************************************************************************
 * @file    send_request.hpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    09-June-2023
 * @brief   Implementation for sendRequest.
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */


/* Own Libs / datatypes */
#include "request_type.h"

#include "message_parser.h"
#include "tcp/tcp_client.hpp"

/**************************************************************************************************
 * Public - Function implementation
 *************************************************************************************************/

template<typename T>
T sendRequest(std::shared_ptr<TcpClient> client, RequestType &request) {
  //normal implementation
  
}

template<>
void sendRequest<void>(std::shared_ptr<TcpClient> client, RequestType &request) {
  //void-specific implementation
}
