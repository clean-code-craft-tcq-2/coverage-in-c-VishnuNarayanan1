#include "alertConfig.h"
#include "typewise-alert.h"
#include <stdio.h>
#include <stdbool.h>

//In case of production environment following print functionalities are used.
#ifdef PRODUCTION_ENVIRONMENT
void PrintToController (const unsigned short Header, BreachType BreachTypeInfo)
{
      printf("%x : %x\n", Header, BreachTypeInfo);
}

void PrintToEmail (const char* Recepient, char Message[])
{
      printf("To: %s\n%s", Recepient,Message);
}
#endif

//Function to validate if the value is within the limits
BreachType InferBreach(double Value, BatteryParam_st BatteryLimits) 
{
  if(Value < BatteryLimits.lowerLimitTemp) {return TOO_LOW;}
  if(Value > BatteryLimits.higherLimitTemp) { return TOO_HIGH;}
  return NORMAL;
}

//Function to fill the temperature limits based on cooling type.
// Here, status is added to check if the passed cooling type is valid, if not the status would be set to false.
BatteryParam_st ClassifyTemp(CoolingType CoolingTypeInfo)
{
  BatteryParam_st batteryParameters; 
  batteryParameters.status = validateRange(CoolingTypeInfo,MAX_COOLING_TYPES);
  batteryParameters.coolingType = CoolingTypeInfo;
  batteryParameters.lowerLimitTemp = BatteryParamValues[coolingType].lowerLimitTemp;
  batteryParameters.higherLimitTemp = BatteryParamValues[coolingType].higherLimitTemp;
  return batteryParameters;
}

// Utility function to validate if the variable 1 is within the specified range.
bool ValidateRange(size_t Var1, size_t Var2)
{
  if((Var1 > 0) && (Var1 < Var2)) { return true;} 
  return false;
}

// This function is to alert the breach to the user.
// Here the value of the alertTarget is checked to ensure that it is within the possible limits configured in alertConfig files.
bool AlertBreach(AlertTarget AlertTargetInfo, BreachType processedBreachType) 
{
  if(validateRange(AlertTargetInfo,MAX_ALERT_TARGET_POSSIBILITIES))
  {
    AlertTargetInfo[AlertTargetInfo].alertTargetFunction(processedBreachType);
    return SUCCESS;
  }
   return FAILURE;
}

// This function makes out the parameters required to send the alert information to controller.
// Note : if in case in the future if any other way of conveying the breach information is introduced,
// without touching any other piece of code, just a function similar to this can be added and configured.
void SendAlertToController(BreachType BreachTypeInfo) 
{
  const unsigned short header = 0xfeed;
  FuncPointerPrintToController(header,BreachTypeInfo);
}

// This function makes out the parameters required to send the alert information through Email.
// Note : if in case in the future if any other way of conveying the breach information is introduced,
// without touching any other piece of code, just a function similar to this can be added and configured.
void SendAlertToEmail(BreachType BreachTypeInfo) 
{
  const char* recepient = "a.b@c.com";
  if(MailNotificationInfo[BreachTypeInfo].mailNotification == REQUIRED)
  {
    FuncPointerPrintToEmail(recepient,AlertMessageOverEmail[BreachTypeInfo]);
  }
}


bool ValidateBattery(AlertTarget AlertTargetInfo, CoolingType CoolingTypeInfo, double TemperatureInC)
{
  BatteryParam_st batteryTempLimits;
  BreachType processedBreachType;
  bool status;
  batteryTempLimits = ClassifyTemp(CoolingTypeInfo);
  if(batteryTempLimits.status == SUCCESS)
  {
    processedBreachType = InferBreach(TemperatureInC,batteryTempLimits);
    status = AlertBreach(AlertTargetInfo , processedBreachType);
  }
  return status;
}
