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

BreachMailNotification_st BreachMailNotification[MAX_BREACH_TYPES]=
{
  {
    .breachType    = NORMAL,
    .alertTarget  = TO_CONTROLLER,
  },
  {
    .breachType    = TOO_LOW,
    .alertTarget  = TO_EMAIL,
  },
  {
    .breachType    = TOO_HIGH,
    .alertTarget  = TO_EMAIL,
  }
};


char AlertMessageOverEmail[MAX_BREACH_TYPES][100] =
{"Not Applicable","Hi, the temperature is too low\n","Hi, the temperature is too high\n"};
