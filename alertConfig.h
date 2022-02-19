#define MAX_COOLING_TYPES   3
#define MAX_BREACH_TYPES    3
#define INVALID_TEMPERATURE 0xff

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
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef enum {
  Required,
  NotRequired
} MailNotification;

typedef struct {
  CoolingType coolingType;
  double lowerLimitTemp;
  double higherLimitTemp;
} BatteryParam_st;

typedef struct {
  BreachType breachType;
  MailNotification mailNotification;
} BreachMailNotification_st;
  

extern struct BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES];
extern struct BreachMailNotification_st BreachMailNotification[MAX_BREACH_TYPES];
extern char AlertMessageOverEmail[MAX_BREACH_TYPES][100];
