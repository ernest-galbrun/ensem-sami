//WORLD DEFINITIONS
#define TIME_STEP 10
#define PI 3.14159265

//TRACK DEFINITIONS
#define KX 0.7 // mm/s
#define KY 0.7 // mm/s
#define OSX 0 // mm
#define OSY 0 // mm

//ROBOT DEFINITIONS
#define NB_SENSORS 9
#define AXIS 89 //mm
#define K_SPEED 70 // 555.6//138.9 (value if x4 is used
#define K_ENCODER 0.097 // 0.18634 //0.047 (value if x4 used) // mm/pulse

//INITIAL POSITION 
#define X0 0 //mm
#define Y0 0 //mm
#define THETA0 0 //rad

//TRACK CONTROL
#define Kpv 0.2
#define Kpw 0.6
#define EPSILON 2

//FORMATION CONTROL
#define D1 180
#define D0 40
#define ALFA 4
#define GAMA 1

//OBSTACLE CONTROL
#define THRESHOLD 300