/**
  *************************************************************************************************
  * @file    datatypes.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    16-May-2023
  * @brief   
  *************************************************************************************************
  */

#ifndef DATATYPES_H_
#define DATATYPES_H_

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <iostream>
#include <string>
#include <vector>
#include <map>

/**************************************************************************************************
 * MACROS
 *************************************************************************************************/
using namespace std;

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef struct T_TopicType              T_Topic;                              /*!< forward declaration for T_Topic */

typedef vector<string>                  T_SubscriberList;                     /*!< list of subscribers */
typedef vector<T_Topic>                 T_TopicList;                          /*!< list of topics */
typedef map<string, T_SubscriberList>   T_TopicSubscriberList;                /*!< list of topics with all their respective subscribers */


typedef struct {
  bool                                  IsTopicAvailable;
  int32_t                               Timestamp;
  T_SubscriberList                      SubscriberList_t;
} T_TopicStatus;                                                              /*!< current status of a topic */

typedef struct {
  T_Action                              Action_t;
  map<string, string>                   ParameterList;
  int32_t                               Timestamp;
} T_Message;                                                                  /*!< message type for communication between publisher and broker */

enum class T_Action {};

enum class T_Status {TopicNotAvailable, IncorrectParameters, InternalError};

struct T_TopicType {
  string                                TopicName;
  T_Message                             Message_t;
};

#endif /* DATATYPES_H_ */
