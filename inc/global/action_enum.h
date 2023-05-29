/**
  *************************************************************************************************
  * @file    action_enum.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    29-May-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
class ACTION_ENUM {
  public:
    enum Action : uint8_t {
      SUBSCRIBE_TOPIC,
      UNSUBSCRIBE_TOPIC,
      PUBLISH_TOPIC,
      LIST_TOPICS,
      GET_TOPIC_STATUS,
      UPDATE_TOPIC
    };

    ACTION_ENUM() = default;
    constexpr ACTION_ENUM(Action action) : m_Action(action) {}

    constexpr operator Action() const {return m_Action;}    //enable switch(Action) use case
    explicit operator bool() const = delete;

    std::string toString() const {
      switch(m_Action) {
        case SUBSCRIBE_TOPIC:
          return "SUBSCRIBE_TOPIC";
        case UNSUBSCRIBE_TOPIC:
          return "UNSUBSCRIBE_TOPIC";
        case PUBLISH_TOPIC:
          return "PUBLISH_TOPIC";
        case LIST_TOPICS:
          return "LIST_TOPICS";
        case GET_TOPIC_STATUS:
          return "GET_TOPIC_STATUS";
        case UPDATE_TOPIC:
          return "UPDATE_TOPIC";
        default:
          return "Error";
      }
    }

    void fromString(std::string valueString) {
      if(valueString=="SUBSCRIBE_TOPIC") m_Action = SUBSCRIBE_TOPIC;
      else if(valueString=="UNSUBSCRIBE_TOPIC") m_Action = UNSUBSCRIBE_TOPIC;
      else if(valueString=="PUBLISH_TOPIC") m_Action = PUBLISH_TOPIC;
      else if(valueString=="LIST_TOPICS") m_Action = LIST_TOPICS;
      else if(valueString=="GET_TOPIC_STATUS") m_Action = GET_TOPIC_STATUS;
      else if(valueString=="UPDATE_TOPIC") m_Action = UPDATE_TOPIC;
    }

  private:
    Action m_Action;
};
