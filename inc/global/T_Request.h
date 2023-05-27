/**
  *************************************************************************************************
  * @file    T_Request.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    27-May-2023
  * @brief   Type definition for request for communication between publisher/subscriber and broker 
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <map>
#include <string>
#include "action_enum.h"


/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef struct {
  ACTION_ENUM                             Action_t;
  std::map<std::string, std::string>      ParameterList;
  int32_t                                 Timestamp;
} T_Request; /*!< type definition for request for communication between publisher/subscriber and broker */
