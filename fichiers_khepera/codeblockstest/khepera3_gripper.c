
/*!
 * (c) 2013 - 2014 ENSEM, Nancy, France
 * Beneux Gaetan
 *
 * Based on
 * (c) 2006 - 2008 EPFL, Lausanne, Switzerland
 * Thomas Lochmatter
 */
#include <i2cal/i2cal.h>
#include "khepera3_gripper.h"
/*** Module initialization ***/

/*** Register read ***/

struct sI2CAL i2cal;


int khepera3_gripper_read_register8_p(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register8 reg, unsigned int *result)
{
    struct i2c_msg *msg_read;

    // Send register and read value
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_write(gripper->i2c_address);
    msg_read = i2cal_read(gripper->i2c_address, 1);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    // Parse value and return
    //printf("gripper read %d\n", msg_read->buf[0]);
    *result = msg_read->buf[0];
    return -1;
}

int khepera3_gripper_read_register16_p(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register16 reg, unsigned int *result)
{
    struct i2c_msg *msg_read;
    unsigned int value;

    // Note that this should ideally be a single commit - one of the following possibilites:
    //   (1) S write reg S read 2 P
    //   (2) S write reg1 S read 1 [P] S write reg2 S read 1 P
    // Method (1) doesn't work because the firmware only allows reading/writing 8 bit messages at a time.
    // Method (2) doesn't work for some reason because the Linux Kernel 2.4 currently in use on the robots seems to generate wrong signals then. In addition, there is no way to generate the stop bit [P] between the two register reads while keeping it in one commit. The only solution would be to synchronize using something else (e.g. file lock).

    // Send register and read value (for H register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg + 1);
    i2cal_write(gripper->i2c_address);
    msg_read = i2cal_read(gripper->i2c_address, 1);
    if (i2cal_commit() < 0)
    {
        return 0;
    }
    value = msg_read->buf[0] << 8;
    //printf("gripper read H %d\n", msg_read->buf[0]);

    // Send register and read value (for L register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_write(gripper->i2c_address);
    msg_read = i2cal_read(gripper->i2c_address, 1);
    if (i2cal_commit() < 0)
    {
        return 0;
    }
    value |= msg_read->buf[0];
    //printf("gripper read L %d\n", msg_read->buf[0]);

    // Return success1
    *result = value;
    return -1;
}

int khepera3_arm_read_register8_p(struct Khepera3_arm *arm, enum Khepera3_arm_register8 reg, unsigned int *result)
{
    struct i2c_msg *msg_read;

    // Send register and read value
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_write(arm->i2c_address);
    msg_read = i2cal_read(arm->i2c_address, 1);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    // Parse value and return
    //printf("arm read %d\n", msg_read->buf[0]);
    *result = msg_read->buf[0];
    return -1;
}

int khepera3_arm_read_register16_p(struct Khepera3_arm *arm, enum Khepera3_arm_register16 reg, unsigned int *result)
{
    struct i2c_msg *msg_read;
    unsigned int value;

    // Note that this should ideally be a single commit - one of the following possibilites:
    //   (1) S write reg S read 2 P
    //   (2) S write reg1 S read 1 [P] S write reg2 S read 1 P
    // Method (1) doesn't work because the firmware only allows reading/writing 8 bit messages at a time.
    // Method (2) doesn't work for some reason because the Linux Kernel 2.4 currently in use on the robots seems to generate wrong signals then. In addition, there is no way to generate the stop bit [P] between the two register reads while keeping it in one commit. The only solution would be to synchronize using something else (e.g. file lock).

    // Send register and read value (for H register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg + 1);
    i2cal_write(arm->i2c_address);
    msg_read = i2cal_read(arm->i2c_address, 1);
    if (i2cal_commit() < 0)
    {
        return 0;
    }
    value = msg_read->buf[0] << 8;
    //printf("arm read H %d\n", msg_read->buf[0]);

    // Send register and read value (for L register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_write(arm->i2c_address);
    msg_read = i2cal_read(arm->i2c_address, 1);
    if (i2cal_commit() < 0)
    {
        return 0;
    }
    value |= msg_read->buf[0];
    //printf("arm read L %d\n", msg_read->buf[0]);

    // Return success1
    *result = value;
    return -1;
}

/*** Register write ***/

int khepera3_gripper_write_register8(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register8 reg, unsigned int value)
{
    // Send register and read value
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_writedata_uint8(value);
    i2cal_write(gripper->i2c_address);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    return -1;
}

int khepera3_gripper_write_register16(struct Khepera3_gripper *gripper, enum Khepera3_gripper_register16 reg, unsigned int value)
{
    // Send register and read value (for H register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg + 1);
    i2cal_writedata_uint8((value >> 8) & 0xff);
    i2cal_write(gripper->i2c_address);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    // Send register and read value (for L register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_writedata_uint8(value & 0xff);
    i2cal_write(gripper->i2c_address);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    return -1;
}

int khepera3_arm_write_register8(struct Khepera3_arm *arm, enum Khepera3_arm_register8 reg, unsigned int value)
{
    // Send register and read value
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_writedata_uint8(value);
    i2cal_write(arm->i2c_address);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    return -1;
}

int khepera3_arm_write_register16(struct Khepera3_arm *arm, enum Khepera3_arm_register16 reg, unsigned int value)
{
    // Send register and read value (for H register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg + 1);
    i2cal_writedata_uint8((value >> 8) & 0xff);
    i2cal_write(arm->i2c_address);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    // Send register and read value (for L register)
    i2cal_start();
    i2cal_writedata_uint8((unsigned int)reg);
    i2cal_writedata_uint8(value & 0xff);
    i2cal_write(arm->i2c_address);
    if (i2cal_commit() < 0)
    {
        return 0;
    }

    return -1;
}
/*!
* //////////////////////////////
* ////// GRIPPER FUNCTION //////
* //////////////////////////////
*/
//!Fonction Read Gripper
int khepera3_gripper_getFirmware(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register8_p(gripper,Khepera3_gripper_register8_FirmwareVersion,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture FirmwareVersion" << endl;
        return 0;
    }
    gripper->firmware_version=value;
    return -1;
}
int khepera3_gripper_actual_position(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register8_p(gripper,Khepera3_gripper_register8_ActualPosition,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture actual_position" << endl;
        return 0;
    }
    gripper->actual_position=value;
    return -1;
}
int khepera3_gripper_actual_speed(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register8_p(gripper,Khepera3_gripper_register8_ActualSpeed,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture actual_speed" << endl;
        return 0;
    }
    gripper->actual_speed=value;
    return -1;
}
int khepera3_gripper_actual_motor_current(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register8_p(gripper,Khepera3_gripper_register16_ActualMotorCurrent,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture FirmwareVersion" << endl;
        return 0;
    }
    gripper->actual_motor_current=value;
    return -1;
}

int khepera3_gripper_object_resistivity(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register16_p(gripper,Khepera3_gripper_register16_ObjectResisivity,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture object_resistivity" << endl;
        return 0;
    }
    gripper->object_resistivity=value;
    return -1;
}

int khepera3_gripper_light_left(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register16_p(gripper,Khepera3_gripper_register16_LeftAmbientLight,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture light_left" << endl;
        return 0;
    }
    gripper->light_left=value;
    return -1;
}

int khepera3_gripper_light_right(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register16_p(gripper,Khepera3_gripper_register16_RightAmbientLight,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture light_right" << endl;
        return 0;
    }
    gripper->light_right=value;
    return -1;
}

int khepera3_gripper_distance_left(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register16_p(gripper,Khepera3_gripper_register16_LeftDistance,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture distance_left" << endl;
        return 0;
    }
    gripper->distance_left=value;
    return -1;
}

int khepera3_gripper_distance_right(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register16_p(gripper,Khepera3_gripper_register16_RightDistance,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture distance_right" << endl;
        return 0;
    }
    gripper->distance_right=value;
    return -1;
}

int khepera3_gripper_object_detection(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register8_p(gripper,Khepera3_gripper_register8_ObjectDetection,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture object_detection" << endl;
        return 0;
    }
    gripper->object_detection=value;
    return -1;
}

int khepera3_gripper_mechanical_limit(struct Khepera3_gripper *gripper)
{
    int res;
    unsigned int value;

    res = khepera3_gripper_read_register8_p(gripper,Khepera3_gripper_register8_MechanicalLimit,&value);
    if(res ==0)
    {
//        cout << "Erreur lecture mechanical_limit" << endl;
        return 0;
    }
    gripper->mechanical_limit=value;
    return -1;
}


//!Fonction Write Gripper
int khepera3_gripper_positionOrder(struct Khepera3_gripper *gripper, int positionOrder)
{
    khepera3_gripper_write_register8(gripper,Khepera3_gripper_register8_PositionOrder,positionOrder);
}


/*!
* //////////////////////////
* ////// ARM FUNCTION //////
* //////////////////////////
*/
//!Fonction Read Arm
int khepera3_arm_getFirmware(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res = khepera3_arm_read_register8_p(arm,Khepera3_arm_register8_FirmwareVersion,&value);
    if(res == 0)
    {
//        cout << "Erreur lecture FirmwareVersion" << endl;
        return 0;
    }
    arm->firmware_version=value;
    return -1;
}

int khepera3_arm_remaining_battery_capacity(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res=khepera3_arm_read_register8_p(arm,Khepera3_arm_register8_BatteryRemainingCapacity,&value);
    if(res == 0)
    {
//        cout << "Erreur lecture BatteryRemainingCapacity" << endl;
        return 0;
    }
    arm->remaining_battery_capacity=value;
    return -1;
}

int khepera3_arm_actual_speed(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res=khepera3_arm_read_register8_p(arm,Khepera3_arm_register8_ActualSpeed,&value);
    if(res == 0)
    {
//        cout << "Erreur lecture ActualSpeed" << endl;
        return 0;
    }
    arm->actual_speed=value;
    return -1;
}

int khepera3_arm_battery_voltage(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res=khepera3_arm_read_register16_p(arm,Khepera3_arm_register16_BatteryVoltage, &value);
    if(res == 0)
    {
//        cout << "Erreur lecture BatteryVoltage" << endl;
        return 0;
    }
    arm->battery_voltage=value;
    return -1;
}

int khepera3_arm_actual_position(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;
    res = khepera3_arm_read_register16_p(arm,Khepera3_arm_register16_ActualPosition, &value);
    if(res == 0)
    {
//        cout << "Erreur lecture ActualPosition" << endl;
        return 0;
    }
    arm->actual_position=value;
    return -1;
}

int khepera3_arm_actual_motor_current(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res=khepera3_arm_read_register16_p(arm,Khepera3_arm_register16_ActualMotorCurrent, &value);
    if(res == 0)
    {
//        cout << "Erreur lecture ActualMotorCurrent" << endl;
        return 0;
    }
    arm->actual_motor_current=value;
    return -1;
}

int khepera3_arm_mechanical_limit_high(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res=khepera3_arm_read_register16_p(arm,Khepera3_arm_register16_HighMechanicalLimit, &value);
    if(res == 0)
    {
//        cout << "Erreur lecture HighMechanialLimit" << endl;
        return 0;
    }
    arm->mechanical_limit_high=value;
    return -1;
}

int khepera3_arm_mechanical_limit_ground(struct Khepera3_arm *arm)
{
    int res;
    unsigned int value;

    res=khepera3_arm_read_register16_p(arm,Khepera3_arm_register16_GroundMechanicalLimit, &value);
    if(res == 0)
    {
//        cout << "Erreur lecture GroundMechanicalLimit" << endl;
        return 0;
    }
    arm->mechanical_limit_ground=value;
    return -1;
}

//!Fonction Write Arm
int khepera3_arm_positionOrder(struct Khepera3_arm *arm, int order)
{
    khepera3_arm_write_register16(arm,Khepera3_arm_register16_PositionOrder,order);
}

int khepera3_arm_Maximumspeed(struct Khepera3_arm *arm, int order)
{
    khepera3_arm_write_register8(arm,Khepera3_arm_register8_MaximumSpeed,order);
}
