//WORLD DEFINITIONS
#define TIME_STEP 10
#define PI 3.14159265

//TRACK DEFINITIONS
#define KX 7 // cm/s
#define KY 7 // cm/s
#define OSX 0 // cm
#define OSY 0 // cm

//ROBOT DEFINITIONS
#define NB_SENSORS 9
#define AXIS 8.9 //cm
#define K_SPEED 1440.1
#define K_ENCODER 0.0047 // cm/pulse

//INITIAL POSITION 
#define X0 0 //cm
#define Y0 0 //cm
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