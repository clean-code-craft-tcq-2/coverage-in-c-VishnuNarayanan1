#include "alertConfig.h"
#include "typewise-alert.h"
#include <stdio.h>
#include <stdbool.h>

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
  batteryParameters.status = validateRange(coolingType,MAX_COOLING_TYPES);
  batteryParameters.coolingType = coolingType;
  batteryParameters.lowerLimitTemp = BatteryParamValues[coolingType].lowerLimitTemp;
  batteryParameters.higherLimitTemp = BatteryParamValues[coolingType].higherLimitTemp;
  return batteryParameters;
}

bool validateRange(size_t var1, size_t var2)
{
  if(var1 > 0 && var1 < var2)
  {
    return true;
  } 
  return false;
}


void alertBreach(AlertTarget alertTarget, BreachType processedBreachType) 
{
  fnptr();
  
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

void PrintToController (header, breachType)
{
      printf("%x : %x\n", header, breachType);
}

void PrintToEmail (recepient, message)
{
      printf(""To: %s\n%s", recepient,message);
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
  if(BreachMailNotification[breachType].mailNotification == Required)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
}


void test(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC)
{
  BatteryParam_st batteryTempLimits;
  BreachType processedBreachType;
  batteryTempLimits = classifyTemp(coolingType);
  if(batteryTempLimits.status == SUCCESS)
  {
    processedBreachType = inferBreach(temperatureInC,batteryTempLimits);
    alertBreach(alertTarget , processedBreachType);
  }
}
