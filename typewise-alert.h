#pragma once

BreachType inferBreach(double value, BatteryParam_st batteryLimits);
void alertBreach(AlertTarget alertTarget, BreachType processedBreachType);
void sendAlertToController(BreachType breachType);
void sendAlertToEmail(BreachType breachType);
BatteryParam_st classifyTemp(CoolingType coolingType);
void test(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC);
bool validateRange(size_t var1, size_t var2);
