#include <stddef.h>
#define MAX_COOLING_TYPES   3
#define INVALID_TEMPERATURE 0xff
#define SUCCESS true
#define FAILURE false

typedef void (*FnPtrAlertTarget)(BreachType);
typedef void (*FnPtrPrintToController)(const unsigned short header, BreachType breachType);
typedef void (*FnPtrPrintToEmail)(const char* recepient, char message[]);

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

typedef enum{
  REQUIRED,
  NOT_REQUIRED
}MailNotification;

typedef struct {
  CoolingType coolingType;
  double lowerLimitTemp;
  double higherLimitTemp;
  bool status;
} BatteryParam_st;

typedef struct 
{
  AlertTarget alertTarget;
  FnPtrAlertTarget alertTargetFunction;
}AlertTarget_st;

typedef struct 
{
  BreachType breachType;
  MailNotification mailNotification;
}MailNotification_st;

extern MailNotification_st MailNotificationInfo[MAX_BREACH_TYPES];
extern AlertTarget_st AlertTargetInfo[MAX_ALERT_TARGET_POSSIBILITIES];
extern BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES];
extern char AlertMessageOverEmail[MAX_BREACH_TYPES][100];
extern FnPtrPrintToController FuncPointerPrintToController;
extern FnPtrPrintToEmail FuncPointerPrintToEmail;
