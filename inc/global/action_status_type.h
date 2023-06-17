/***************************************************************************************************
 * @file    action_status_type.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    01-June-2023
 * @brief   Datatype for ActionStatus
 **************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
class ActionStatusType {
  public:
    enum ActionStatus : uint8_t {
      STATUS_OK,
      TOPIC_NON_EXISTENT,
      INVALID_PARAMETERS,
      INTERNAL_ERROR
    };

    ActionStatusType() = default;
    constexpr ActionStatusType(ActionStatus actionStatus) : m_ActionStatus(actionStatus) {}

    constexpr operator ActionStatus() const {return m_ActionStatus;}    //enable switch(Action) use case
    explicit operator bool() const = delete;

    std::string toString() const {
      switch(m_ActionStatus) {
        case STATUS_OK:
          return "STATUS_OK";
        case TOPIC_NON_EXISTENT:
          return "TOPIC_NON_EXISTENT";
        case INVALID_PARAMETERS:
          return "INVALID_PARAMETERS";
        case INTERNAL_ERROR:
          return "INTERNAL_ERROR";
        default:
          return "Error";
      }
    }

  private:
    ActionStatus m_ActionStatus;
};
