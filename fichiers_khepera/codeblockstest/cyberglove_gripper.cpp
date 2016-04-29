/*!
 * (c) 2013 - 2014 ENSEM, Nancy, France
 * Beneux Gaetan
 *
 */

//#include "khepera3/khepera3.h"
#include "khepera3_gripper.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <i2cal/i2cal.h>
#include <sys/ioctl.h>
#include <boost/thread.hpp>


extern struct sI2CAL i2cal;


using namespace std;
int FinProg;
struct i2c_msg msg_read;
struct Khepera3_gripper gripper;
struct Khepera3_arm arm;
int position_glove_gripper;
int position_glove_arm;
int gripper_prec;
int arm_prec;

void thread_actualisation()
{
    while(1)
    {
        /*!
         * Ce thread permet de lire et de mettre a jour en permanence les valeurs des
         * angles, positions et autre information capteur du gripper et de l'arm.
         * Il permet d'etre a jour, meme en cas de mouvement forcé manuellement,
         * ou de blocage
         */
        //cout<< "thread_actu" <<endl;
//!Khepera3_arm actu
        khepera3_arm_battery_voltage(&arm);
        khepera3_arm_actual_speed(&arm);
        khepera3_arm_actual_position(&arm);
        khepera3_arm_actual_motor_current(&arm);
        khepera3_arm_remaining_battery_capacity(&arm);
        khepera3_arm_mechanical_limit_ground(&arm);
        khepera3_arm_mechanical_limit_high(&arm);
//!Khepera3_gripper actu
        khepera3_gripper_actual_position(&gripper);
        khepera3_gripper_actual_speed(&gripper);
        khepera3_gripper_actual_motor_current(&gripper);
        khepera3_gripper_object_resistivity(&gripper);
        khepera3_gripper_light_left(&gripper);
        khepera3_gripper_light_right(&gripper);
        khepera3_gripper_distance_left(&gripper);
        khepera3_gripper_distance_right(&gripper);
        khepera3_gripper_object_detection(&gripper);
        khepera3_gripper_mechanical_limit(&gripper);
        boost::this_thread::sleep(boost::posix_time::millisec(1000));
    }
}

void thread_mouvement_gripper()
{
    while(1)
    {
        //cout<< "thread_mouv" <<endl;
        /*!
         *Ce thread permet de mettre en mouvement
         *le gripper sans feedback.
         */
//!Mouvoir le gripper
        //cout<< "gripper ::" <<gripper.actual_position<< " "<< position_glove_gripper << endl;
        if(gripper.actual_position != position_glove_gripper)
        {
            if(gripper.actual_position < position_glove_gripper)
            {
                khepera3_gripper_positionOrder(&gripper,gripper.actual_position+gripper_prec);
                gripper.actual_position=gripper.actual_position+gripper_prec;
            }
            if(gripper.actual_position > position_glove_gripper)
            {
                khepera3_gripper_positionOrder(&gripper,gripper.actual_position-gripper_prec);
                gripper.actual_position=gripper.actual_position-gripper_prec;
            }
        }
    }
}
void thread_mouvement_arm()
{
    while(1)
    {
        /*!
        *Ce thread permet de mettre en mouvement
        *l'arm sans feedback.
        */
//!Mouvoir l'arm
        //cout<< "arm ::" <<arm.actual_position<< " "<< position_glove_arm << endl;
        if(arm.actual_position != position_glove_arm)
        {
                khepera3_arm_positionOrder(&arm,position_glove_arm);
        }
    }
}

void UpdateGripperTarget(int arm_target, int gripper_target)
{
    static bool first_call = true;
    if(first_call){
        gripper.i2c_address=0x15;
        arm.i2c_address=0x14;
        position_glove_gripper=0;
        position_glove_arm=0;
        gripper_prec=1;
        arm_prec=1;
        int choix;
        //khepera3_init();
        cout << "init ok\n";
        khepera3_arm_Maximumspeed(&arm,15);
        khepera3_gripper_getFirmware(&gripper);
        cout << "Version du Firmware = " << gripper.firmware_version << endl;
        khepera3_gripper_positionOrder(&gripper,0);
        cout << "Gripper Deplacé" << endl;
        khepera3_arm_positionOrder(&arm,0);
        cout << "Arm déplacé" << endl;
        cout << arm.actual_position << endl;
        cout << "Pret pour utilisation" << endl;

        boost::thread ThreadActu(&thread_actualisation);
        boost::thread ThreadMouvGripper(&thread_mouvement_gripper);
        boost::thread ThreadMouvArm(&thread_mouvement_arm);

        cout << "Les limites de l'arm sont :" << arm.mechanical_limit_ground << "et" << arm.mechanical_limit_high << endl;
        cout << "La limite du gripper est :" << gripper.mechanical_limit << endl;
        first_call = false;
        }
    position_glove_gripper = gripper_target;
    position_glove_arm = arm_target;
}

