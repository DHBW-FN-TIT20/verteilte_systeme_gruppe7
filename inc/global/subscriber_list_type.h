/**
  *************************************************************************************************
  * @file    subscriber_list_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <vector>
#include "subscriber_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef std::vector<T_Subscriber>  T_SubscriberList;   /*!< type definition for list of subscribers identified by their names */
