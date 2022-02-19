#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "alertConfig.h"
#include "typewise-alert.h"

// Note : For the test environment stub for all the print interfaces used
#ifdef TEST_ENVIRONMENT
int Test_PrintToControllerStubCount;
int Test_PrintToEmailStubCount;
void PrintToControllerStub (const unsigned short Header, BreachType BreachTypeInfo)
{
      Test_PrintToControllerStubCount++;
}
void PrintToEmailStub (const char* Recepient, char Message[])
{
      Test_PrintToEmailStubCount++;
}
FnPtrPrintToController FuncPointerPrintToController = &PrintToControllerStub;
FnPtrPrintToEmail FuncPointerPrintToEmail = &PrintToEmailStub;
#endif 

TEST_CASE("Temperature value passed is less than lower limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 15;
  REQUIRE(InferBreach(value, BatteryLimits) == TOO_LOW);
}


TEST_CASE("Temperature value passed is more than higher limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 60;
  REQUIRE(InferBreach(value, BatteryLimits) == TOO_HIGH);
}


TEST_CASE("Temperature value passed is less than lower limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 30;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}
