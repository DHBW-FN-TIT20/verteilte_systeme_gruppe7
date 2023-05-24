/**
  *************************************************************************************************
  * @file    T_ActionStatus.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    23-May-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
enum class T_ActionStatus {
  STATUS_OK,
  TOPIC_NON_EXISTENT,
  INVALID_PARAMETERS,
  INTERNAL_ERROR
}; /*!< enum for status codes that indicate whether an action was performed successfully or which errors occured */
