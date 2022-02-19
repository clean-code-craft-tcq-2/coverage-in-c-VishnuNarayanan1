#pragma once

BreachType inferBreach(double value, BatteryParam_st batteryLimits);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
BatteryParam_st classifyTemp(CoolingType coolingType);
void test(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC);
