#include <stddef.h>
#define MAX_COOLING_TYPES   3
#define INVALID_TEMPERATURE 0xff
#define SUCCESS true
#define FAILURE false

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  INVALID_COOLING_TYPE = 0xff
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  MAX_BREACH_TYPES
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  MAX_ALERT_TARGET_POSSIBILITIES
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  double lowerLimitTemp;
  double higherLimitTemp;
} BatteryParam_st;

typedef void (*FnPtrAlertTarget)(BreachType);

typedef struct 
{
  AlertTarget alertTarget;
  FnPtrAlertTarget alertTargetFunction;
}AlertTarget_st;

extern AlertTarget_st AlertTargetInfo[MAX_ALERT_TARGET_POSSIBILITIES];
extern BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES];
extern char AlertMessageOverEmail[MAX_BREACH_TYPES][100];
