#pragma once

BreachType inferBreach(double value, BatteryParam_st batteryLimits);
void alertBreach(AlertTarget alertTarget, BreachType processedBreachType);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
BatteryParam_st classifyTemp(CoolingType coolingType);
void test(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC);
bool validateRange(size_t var1, size_t var2);
