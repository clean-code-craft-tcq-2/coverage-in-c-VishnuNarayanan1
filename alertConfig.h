#define MAX_COOLING_TYPES   3
#define MAX_BREACH_TYPES    3
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
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  double lowerLimitTemp;
  double higherLimitTemp;
} BatteryParam_st;


extern BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES];
extern char AlertMessageOverEmail[MAX_BREACH_TYPES][100];
