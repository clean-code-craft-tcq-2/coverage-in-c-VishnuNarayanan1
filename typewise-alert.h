#pragma once

BreachType InferBreach(double Value, BatteryParam_st BatteryLimits);
bool AlertBreach(AlertTarget AlertTarget, BreachType ProcessedBreachType);
void SendAlertToController(BreachType breachType);
void SendAlertToEmail(BreachType breachType);
BatteryParam_st ClassifyTemp(CoolingType CoolingTypeInfo);
bool ValidateBattery(AlertTarget AlertTargetIndex, CoolingType CoolingTypeInfo, double TemperatureInC);
bool ValidateRange(size_t Var1, size_t Var2);
void PrintToController (const unsigned short Header, BreachType BreachTypeInfo);
void PrintToEmail (const char* Recepient, char Message[]);
