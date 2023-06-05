/**************************************************************************************************
 * @file    send_request.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
/* Own Libs / datatypes */
#include "message_parser.h"
#include "request_type.h"

/**************************************************************************************************
 * Public - Function implementation
 *************************************************************************************************/

/**
 * @brief send a request and expect an answer
 * 
 * @tparam T expected return type for the response
 * @param request request to be converted to json and sent to the network
 * @param pt_NetworkHandler Pointer to network handler to be used for the transmission
 * @return T response without action status
 */
template<typename T>
T sendRequest(RequestType request, INetworkHandler* pt_NetworkHandler) {
  //normal implementation
}

/**
 * @brief send a request without expecting an answer (message)
 * 
 * @param request request to be converted to json and sent to the network
 * @param pt_NetworkHandler Pointer to network handler to be used for the transmission
 */
template<>
void sendRequest<void>(RequestType request, INetworkHandler* pt_NetworkHandler) {
  //void-specific implementation
}