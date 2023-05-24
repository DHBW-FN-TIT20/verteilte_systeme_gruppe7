/**
  *************************************************************************************************
  * @file    T_Action.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    24-May-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
enum class T_Action {
  SUBSCRIBE_TOPIC,
  UNSUBSCRIBE_TOPIC,
  PUBLISH_TOPIC,
  LIST_TOPICS,
  GET_TOPIC_STATUS,
  UPDATE_TOPIC
}; /*!< enum for action codes that define which action should be triggered in the receiver */
