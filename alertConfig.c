#include <stdio.h>
#include <stdbool.h>
#include "alertConfig.h"

BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES] =
{
  {
  .coolingType =  PASSIVE_COOLING,
  .lowerLimitTemp = 0,
  .higherLimitTemp = 35
  },
  {
  .coolingType =  HI_ACTIVE_COOLING,
  .lowerLimitTemp = 0,
  .higherLimitTemp = 45
  },
  {
  .coolingType = MED_ACTIVE_COOLING,
  .lowerLimitTemp = 0,
  .higherLimitTemp = 40
  }
};
AlertTarget_st AlertTargetInfo[MAX_ALERT_TARGET_POSSIBILITIES] =
{
  {
    .alertTarget = TO_CONTROLLER,
    .alertTargetFunction = &sendAlertToController
  },
  {
     .alertTarget = TO_EMAIL
    .alertTargetFunction = &sendAlertToEmail
  }
};


MailNotification_st MailNotification[MAX_BREACH_TYPES] =
{
  {
    .breachType  = NORMAL,
    .mailNotification = NOT_REQUIRED
  },
  {
    .breachType = TOO_LOW,
    .mailNotification = REQUIRED
  },
  {
    .breachType = TOO_HIGH,
    .mailNotification = REQUIRED
  }
};
char AlertMessageOverEmail[MAX_BREACH_TYPES][100] =
{"Not Applicable","Hi, the temperature is too low\n","Hi, the temperature is too high\n"};
