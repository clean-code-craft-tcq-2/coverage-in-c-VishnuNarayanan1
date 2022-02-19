#include "alertConfig.h"
#include <stdio.h>

struct BatteryParam BatteryParamValues[MAX_COOLING_TYPES] =
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
