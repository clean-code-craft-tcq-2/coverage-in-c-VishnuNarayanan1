#include "alertConfig.h"
#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, BatteryParam_st batteryLimits) 
{
  if(value < batteryLimits.lowerLimitTemp) 
  {
    return TOO_LOW;
  }
  if(value > batteryLimits.higherLimitTemp) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}


BatteryParam_st classifyTemp(CoolingType coolingType)
{
  int i = 0;
  BatteryParam_st batteryParameters; 
  batteryParameters.coolingType = INVALID_COOLING_TYPE;
  batteryParameters.lowerLimitTemp = INVALID_TEMPERATURE;
  batteryParameters.higherLimitTemp = INVALID_TEMPERATURE;
  for(i = 0; i < MAX_COOLING_TYPES; i++)
  {
    if(coolingType == BatteryParamValues[i])
    {
      batteryParameters.coolingType = BatteryParamValues[i].coolingType;
      batteryParameters.lowerLimitTemp = BatteryParamValues[i].lowerLimitTemp;
      batteryParameters.higherLimitTemp = BatteryParamValues[i].higherLimitTemp;
    }
  }
  return batteryParameters;
}


void alertBreach(AlertTarget alertTarget, BreachType processedBreachType) 
{
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(processedBreachType);
      break;
    case TO_EMAIL:
      sendToEmail(processedBreachType);
      break;
  }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  int i = 0;
  for(i = 0; i<MAX_BREACH_TYPES; i++)
  {
    if(BreachMailNotification[breachType].mailNotification == Required)
    {
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too low\n");
    }
  }
}


void test(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC)
{
  BatteryParam_st batteryTempLimits;
  BreachType processedBreachType;
  batteryTempLimits = classifyTemp(coolingType);
  processedBreachType = inferBreach(temperatureInC,batteryTempLimits);
  alertBreach(alertTarget , processedBreachType);
}
