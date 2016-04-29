/*!
 * (c) 2013 - 2014 ENSEM, Nancy, France
 * Beneux Gaetan
 *
 * Based on
 * (c) 2006 - 2008 EPFL, Lausanne, Switzerland
 * Thomas Lochmatter
 *
 */

#ifndef KHEPERA3_GRIPPER
#define KHEPERA3_GRIPPER
#include <i2cal/i2cal.h>

 #ifdef __cplusplus
 extern "C" {
 #endif
enum Khepera3_arm_register8{

    Khepera3_arm_register8_FirmwareVersion            =0x30,//R
    Khepera3_arm_register8_ActualSpeed                =0x33,//R
    Khepera3_arm_register8_OnTargetFlag               =0x36,//R
    Khepera3_arm_register8_BatteryRemainingCapacity   =0x39,//R
    Khepera3_arm_register8_MaximumSpeed               =0x40,//R/W
    Khepera3_arm_register8_SearchLimitFlag            =0x41,//R/W
};

enum Khepera3_arm_register16{

    Khepera3_arm_register16_ActualPosition            =0x31,//R
    Khepera3_arm_register16_ActualMotorCurrent        =0x34,//R
    Khepera3_arm_register16_BatteryVoltage            =0x37,//R
    Khepera3_arm_register16_GroundMechanicalLimit     =0x3A,//R
    Khepera3_arm_register16_HighMechanicalLimit       =0x3C,//R
    Khepera3_arm_register16_PositionOrder             =0x3E,//R/W
};

enum Khepera3_gripper_register8{

    Khepera3_gripper_register8_FirmwareVersion        =0x30,//R
    Khepera3_gripper_register8_ActualPosition         =0x31,//R
    Khepera3_gripper_register8_PositionOrder          =0x32,//R/W
    Khepera3_gripper_register8_ActualSpeed            =0x33,//R
    Khepera3_gripper_register8_ObjectDetection        =0x42,//R
    Khepera3_gripper_register8_OnTargetFlag           =0x43,//R
    Khepera3_gripper_register8_SearchLimitFlag        =0x44,//R/W
    Khepera3_gripper_register8_MechanicalLimit        =0x45,//R
};

enum Khepera3_gripper_register16{

    Khepera3_gripper_register16_ActualMotorCurrent    =0x34,//R
    Khepera3_gripper_register16_MaximumMotorCurrent   =0x36,//R/W
    Khepera3_gripper_register16_ObjectResisivity      =0x38,//R
    Khepera3_gripper_register16_LeftAmbientLight      =0x3A,//R
    Khepera3_gripper_register16_RightAmbientLight     =0x3C,//R
    Khepera3_gripper_register16_LeftDistance          =0x3E,//R
    Khepera3_gripper_register16_RightDistance         =0x40,//R
};

struct Khepera3_arm{
int i2c_address;
unsigned int firmware_version;
int battery_voltage;
int actual_speed;
int actual_position;
int actual_motor_current;
int remaining_battery_capacity;
int mechanical_limit_ground;
int mechanical_limit_high;
};

struct Khepera3_gripper{
int i2c_address;
unsigned int firmware_version;
int actual_position;
int actual_speed;
int actual_motor_current;
int object_resistivity;
int light_left;
int light_right;
int distance_left;
int distance_right;
int object_detection;
int mechanical_limit;
};



//! Reads an 8 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 4 bytes.
int khepera3_gripper_read_register8_p(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register8 reg, unsigned int *result);
//! Reads a 16 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 8 bytes.
int khepera3_gripper_read_register16_p(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register16 reg, unsigned int *result);
//! Reads an 8 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 4 bytes.
int khepera3_arm_read_register8_p(struct Khepera3_arm *arm, enum Khepera3_arm_register8 reg, unsigned int *result);
//! Reads a 16 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 8 bytes.
int khepera3_arm_read_register16_p(struct Khepera3_arm *arm, enum Khepera3_arm_register16 reg, unsigned int *result);

//! Writes an 8 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 3 bytes.
int khepera3_gripper_write_register8(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register8 reg, unsigned int value);
//! Writes a 16 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 6 bytes.
int khepera3_gripper_write_register16(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register16 reg, unsigned int value);
//! Writes an 8 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 3 bytes.
int khepera3_arm_write_register8(struct Khepera3_arm *arm, enum Khepera3_arm_register8 reg, unsigned int value);
//! Writes a 16 bit register. Returns -1 on success and 0 otherwise. Transfer on I2C bus: 6 bytes.
int khepera3_arm_write_register16(struct Khepera3_arm *arm, enum Khepera3_arm_register16 reg, unsigned int value);

//!Read Function for Gripper
int khepera3_gripper_getFirmware(struct Khepera3_gripper *gripper);
int khepera3_gripper_actual_position(struct Khepera3_gripper *gripper);
int khepera3_gripper_actual_speed(struct Khepera3_gripper *gripper);
int khepera3_gripper_actual_motor_current(struct Khepera3_gripper *gripper);
int khepera3_gripper_object_resistivity(struct Khepera3_gripper *gripper);
int khepera3_gripper_light_left(struct Khepera3_gripper *gripper);
int khepera3_gripper_light_right(struct Khepera3_gripper *gripper);
int khepera3_gripper_distance_left(struct Khepera3_gripper *gripper);
int khepera3_gripper_distance_right(struct Khepera3_gripper *gripper);
int khepera3_gripper_object_detection(struct Khepera3_gripper *gripper);
int khepera3_gripper_mechanical_limit(struct Khepera3_gripper *gripper);


//!Write Function for Gripper
int khepera3_gripper_positionOrder(struct Khepera3_gripper *gripper, int positionOrder);


//!Read Function for Arm
int khepera3_arm_getFirmware(struct Khepera3_arm *arm);
int khepera3_arm_remaining_battery_capacity(struct Khepera3_arm *arm);
int khepera3_arm_actual_speed(struct Khepera3_arm *arm);
int khepera3_arm_battery_voltage(struct Khepera3_arm *arm);
int khepera3_arm_actual_position(struct Khepera3_arm *arm);
int khepera3_arm_actual_motor_current(struct Khepera3_arm *arm);
int khepera3_arm_mechanical_limit_high(struct Khepera3_arm *arm);
int khepera3_arm_mechanical_limit_ground(struct Khepera3_arm *arm);

//!Write Function for Arm
int khepera3_arm_positionOrder(struct Khepera3_arm *arm, int positionOrder);
int khepera3_arm_Maximumspeed(struct Khepera3_arm *arm, int order);


 #ifdef __cplusplus
 }

 #endif

#endif

