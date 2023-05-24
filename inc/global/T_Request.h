/**
  *************************************************************************************************
  * @file    T_Request.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    24-May-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <map>
#include <string>
#include "T_Action.h"


/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef struct {
  T_Action                                Action_t;
  std::map<std::string, std::string>      ParameterList;
  int32_t                                 Timestamp;
} T_Request; /*!< type definition for message for communication between publisher and broker */
