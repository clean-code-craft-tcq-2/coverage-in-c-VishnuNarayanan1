#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include <stdbool.h>
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

TEST_CASE("InferBreach -Temperature value passed is less than lower limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 15;
  REQUIRE(InferBreach(value, BatteryLimits) == TOO_LOW);
}


TEST_CASE("InferBreach - Temperature value passed is more than higher limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 60;
  REQUIRE(InferBreach(value, BatteryLimits) == TOO_HIGH);
}


TEST_CASE("InferBreach - Temperature value passed is in the normal range") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 30;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}

TEST_CASE("InferBreach - Temperature value passed is in the lower boundary") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 20;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}

TEST_CASE("InferBreach -Temperature value passed is in the higher boundary") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 50;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}


TEST_CASE("ClassifyTemp -Positive scenario- PASSIVE_COOLING Cooling Type based lower and upper temperature limit derivation ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(PASSIVE_COOLING);
  REQUIRE(BatteryLimits.status  == SUCCESS);
  REQUIRE(BatteryLimits.coolingType  == PASSIVE_COOLING);
  REQUIRE(BatteryLimits.lowerLimitTemp  == 0);
  REQUIRE(BatteryLimits.higherLimitTemp == 35);
}

TEST_CASE("ClassifyTemp -Positive scenario- HI_ACTIVE_COOLING Cooling Type based lower and upper temperature limit derivation ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(HI_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.status  == SUCCESS);
  REQUIRE(BatteryLimits.coolingType  == HI_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.lowerLimitTemp  == 0);
  REQUIRE(BatteryLimits.higherLimitTemp == 45);
}

TEST_CASE("ClassifyTemp -Positive scenario- MED_ACTIVE_COOLING Cooling Type based lower and upper temperature limit derivation ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(MED_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.status  == SUCCESS);
  REQUIRE(BatteryLimits.coolingType  == MED_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.lowerLimitTemp  == 0);
  REQUIRE(BatteryLimits.higherLimitTemp == 40);
}

TEST_CASE("ClassifyTemp -Negative scenario- INVALID_COOLING_TYPE  Test cooling type which is not under the configured list ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(INVALID_COOLING_TYPE);
  REQUIRE(BatteryLimits.status  == FAILURE);
}

TEST_CASE("ValidateRange -Positive scenario-  On passing 2 input values with (var1 >= 0 && var1 < var2) ") {
  bool ValidateRangeStatus;
  ValidateRangeStatus = ValidateRange (5,10);
  REQUIRE(ValidateRangeStatus  == true);
}

TEST_CASE("ValidateRange -Negative scenario- On passing 2 input values with (var1 >= 0 && var1 > var2) ") {
  bool ValidateRangeStatus;
  ValidateRangeStatus = ValidateRange (15,10);
  REQUIRE(ValidateRangeStatus  == false);
}

TEST_CASE("ValidateRange -Negative scenario- On passing 2 input values with (var1 < 0 && var1 < var2) ") {
  bool ValidateRangeStatus;
  ValidateRangeStatus = ValidateRange (-1,10);
  REQUIRE(ValidateRangeStatus  == false);
}

TEST_CASE("ValidateRange -Negative scenario- On passing 2 input values with (var1 < 0 && var1 > var2) ") {
  bool ValidateRangeStatus;
  ValidateRangeStatus = ValidateRange (-1,-5);
  REQUIRE(ValidateRangeStatus  == false);
}


TEST_CASE("AlertBreach -Positive scenario- Alert message to controller with breach level NORMAL ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (TO_CONTROLLER,NORMAL);
  REQUIRE(AlertBreachStatus  == SUCCESS);
  REQUIRE(Test_PrintToControllerStubCount  == 1);
  REQUIRE(Test_PrintToEmailStubCount  == 0);   
}


TEST_CASE("AlertBreach -Positive scenario- Alert message to controller with breach level TOO_LOW ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (TO_CONTROLLER,TOO_LOW);
  REQUIRE(AlertBreachStatus  == SUCCESS);
  REQUIRE(Test_PrintToControllerStubCount  == 2); 
  REQUIRE(Test_PrintToEmailStubCount  == 0);  
}


TEST_CASE("AlertBreach -Positive scenario- Alert message to controller with breach level TOO_HIGH ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (TO_CONTROLLER,TOO_HIGH);
  REQUIRE(AlertBreachStatus  == SUCCESS);
  REQUIRE(Test_PrintToControllerStubCount  == 3);  
  REQUIRE(Test_PrintToEmailStubCount  == 0);  
}

//NOTE : Since for NORMAL scenario Email notification is configured as not required, Test_PrintToEmailStubCount is expected to remain 0 though
// AlertBreachStatus is SUCCESS
TEST_CASE("AlertBreach -Positive scenario- Alert message through Email with breach level NORMAL ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (TO_EMAIL,NORMAL);
  REQUIRE(AlertBreachStatus  == SUCCESS);
  REQUIRE(Test_PrintToControllerStubCount  == 3); 
  REQUIRE(Test_PrintToEmailStubCount  == 0);  
}


TEST_CASE("AlertBreach -Positive scenario- Alert message through Email with breach level TOO_LOW ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (TO_EMAIL,TOO_LOW);
  REQUIRE(AlertBreachStatus  == SUCCESS);
  REQUIRE(Test_PrintToControllerStubCount  == 3); 
  REQUIRE(Test_PrintToEmailStubCount  == 1);  
}


TEST_CASE("AlertBreach -Positive scenario- Alert message through Email with breach level TOO_HIGH ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (TO_EMAIL,TOO_HIGH);
  REQUIRE(AlertBreachStatus  == SUCCESS);
  REQUIRE(Test_PrintToControllerStubCount  == 3); 
  REQUIRE(Test_PrintToEmailStubCount  == 2);  
}

TEST_CASE("AlertBreach -Negative scenario- Alert message through invalid target with breach level NORMAL ") {
  bool AlertBreachStatus;
  AlertBreachStatus = AlertBreach (INVALID_ALERT_TARGET,NORMAL);
  REQUIRE(AlertBreachStatus  == FAILURE);
  REQUIRE(Test_PrintToControllerStubCount  == 3); 
  REQUIRE(Test_PrintToEmailStubCount  == 2);  
}


TEST_CASE("SendAlertToController - With various possible breach types  ") {
  SendAlertToController (NORMAL);
  REQUIRE(Test_PrintToControllerStubCount  == 4); 
  REQUIRE(Test_PrintToEmailStubCount  == 2);  
  SendAlertToController (TOO_LOW);
  REQUIRE(Test_PrintToControllerStubCount  == 5); 
  REQUIRE(Test_PrintToEmailStubCount  == 2);
  SendAlertToController (TOO_HIGH);
  REQUIRE(Test_PrintToControllerStubCount  == 6); 
  REQUIRE(Test_PrintToEmailStubCount  == 2);
}

TEST_CASE("SendAlertToEmail - With Mail Notification Required - In case of breach level TOO_LOW and TOO_HIGH") {
  SendAlertToEmail (TOO_LOW);
  REQUIRE(Test_PrintToControllerStubCount  == 6); 
  REQUIRE(Test_PrintToEmailStubCount  == 3);  
  SendAlertToEmail (TOO_HIGH);
  REQUIRE(Test_PrintToControllerStubCount  == 6); 
  REQUIRE(Test_PrintToEmailStubCount  == 4);
}

TEST_CASE("SendAlertToEmail - With Mail Notification Not Required - In case of breach level NORMAL") {
  SendAlertToEmail (NORMAL);
  REQUIRE(Test_PrintToControllerStubCount  == 6); 
  REQUIRE(Test_PrintToEmailStubCount  == 4);  
}

