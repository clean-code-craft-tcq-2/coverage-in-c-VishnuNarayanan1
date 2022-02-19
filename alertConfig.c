#include "alertConfig.h"
#include <stdio.h>

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

BreachMailNotification_st BreachMailNotification[MAX_BREACH_TYPES]=
{
  {
    .breachType    = NORMAL,
    .mailNotification = NotRequired
  },
  {
    .breachType    = TOO_LOW,
    .mailNotification = Required
  },
  {
    .breachType    = TOO_HIGH,
    .mailNotification = Required
  }
};
char AlertMessageOverEmail[MAX_BREACH_TYPES][100] =
{"Not Applicable","Hi, the temperature is too low\n","Hi, the temperature is too high\n"};
