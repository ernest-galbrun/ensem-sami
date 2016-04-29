#define BOOST_ASIO_DISABLE_EPOLL //epoll not available on kephera linux distribution

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/thread.hpp"

template<class T> void CheckInputSize(int mandatorySize, const std::vector<T>& input);

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
//
//enum StringValue        {   cmdNotDefined,
//                            cmdGetId,
//                            cmdSetMode,
//                            cmdGetMode,
//                            cmdResetPosition,
//                            cmdSetSpeed,
//                            cmdSetPosition,
//                            cmdSetPoint,
//                            cmdRecordPulse,
//                            cmdSetPID,
//                            cmdGetPID,
//                            cmdGetPosition,
//                            cmdGetSpeed,
//                            cmdSetAcquisitionFrequency1x,
//                            cmdMotorStop,
//                            cmdMotorStart};

int cmdGetID(const std::vector<float>& input, socket_ptr sock);
int cmdSetMode(const std::vector<float>& input, socket_ptr sock);
int cmdGetMode(const std::vector<float>& input, socket_ptr sock);
int cmdResetPosition(const std::vector<float>& input, socket_ptr sock);
int cmdSetSpeed(const std::vector<float>& input, socket_ptr sock);
int cmdSetPosition(const std::vector<float>& input, socket_ptr sock);
int cmdSetPoint(const std::vector<float>& input, socket_ptr sock);
int cmdRecordPulse(const std::vector<float>& input, socket_ptr sock);
int cmdSetPID(const std::vector<float>& input, socket_ptr sock);
int cmdGetPID(const std::vector<float>& input, socket_ptr sock);
int cmdGetPosition(const std::vector<float>& input, socket_ptr sock);
int cmdGetSpeed(const std::vector<float>& input, socket_ptr sock);
int cmdSetAcquisitionFrequency1x(const std::vector<float>& input, socket_ptr sock);
int cmdMotorStop(const std::vector<float>& input, socket_ptr sock);
int cmdMotorStart(const std::vector<float>& input, socket_ptr sock);
int cmdGetInfraredAmbient(const std::vector<float>& input, socket_ptr sock);
int cmdGetInfraredProximity(const std::vector<float>& input, socket_ptr sock);
int cmdGetUltraSound(const std::vector<float>& input, socket_ptr sock);
int cmdResetIR(const std::vector<float>& input, socket_ptr sock);
int cmdFollowLine(const std::vector<float>& input, socket_ptr sock = socket_ptr());
int cmdAllowUDPUpdate(const std::vector<float>& input, socket_ptr sock);
int cmdCross(const std::vector<float>& input, socket_ptr sock);
int cmdGripperGoTo(const std::vector<float>& input, socket_ptr sock);

static std::map<std::string, int(*)(const std::vector<float>&, socket_ptr)> s_mapStringFunctions;

/* Command list and calling syntax :

$GetId :        request robot id
                return values : N (robot Id)


$GetInfraredAmbient : Get infrared ambient values (the higher the IR luminosisty, the lowest the value is)
                      Return values : X[0],...,X[10]
                      BackLeft = 0, Left = 1, FrontSideLeft = 2, FrontLeft = 3, FrontRight = 4, FrontSideRight = 5, Right = 6, BackRight = 7, Back = 8, FloorRight = 9,FloorLeft = 10

$GetInfraredProximity :Get infrared proximity values (the closest we are, the lowest the value is)
                      Return values : X[0],...,X[10]

$GetUltraSound : Get ultrasound sensor echo values
                    return values : echo_count[i],distance[i],amplitude[i],timestamp[i]  (i=0 à 4)
                    Left = 0, FrontLeft = 1, Front = 2, FrontRight = 3, Right = 4

$SetMode,N,K :  set control mode to N(left motor) and K(right motor)
                see khepera3_motor.h : 0 : Open loop
                                       1 : Position
                                       2 : Position using acceleration profile
                                       3 : Speed
                                       4 : Speed using acceleration profile
                                       5 : Torque
                return values : 'SetMode'

$GetMode :      request current regulation mode
                return values : N(left),K(right)

$ResetPosition,N,K : set current position to N,K
                return values : 'ResetPosition'

$SetSpeed,N,K : set control mode to speed regulation for both motors
                and set speed to N(left) and K(right)
                return values : 'SetSpeed'

$SetPosition,N,K : set control mode to position regulation for both motors and set position
                to N(left) and K(right)
                return values : 'SetPosition'

$SetPoint,N,K : set target value to N(left) and K(right) without changing the regulation mode
                return values : 'SetPoint

$RecordPulse,kX,kY,X1,Y1,N1,...,Xn,Yn,Nn : launch a pulse recording, setting target
                setpoint to Xi(left) and Yi(right) for Ni successive acquisition.
                Each acquisition takes around 4 ms to complete.
                Kxn specifies the measure made for the given motor : none (0) position(1) or speed(2)
                return values : t,measureL,measureR for each measurement (t in microsec)

$SetPID,K,M,P,I,D : set PID parameters for the mode specified with K (0 : position, 1 : speed, 2 : torque)
                for the motor M (0:left, 1:right)
                return values : 'SetPID'

$GetPID,K,M :   Request PID coefficient for the mode specified with K (0 : position, 1: speed, 2 : torque)
                for the motor M (0:left, 1:right)
                return values : P,I,D

$GetPosition :  record current position for both motors
                return values : position_left,position_right

$GetSpeed :     record current speed for both motors
                return values : speed_left,speed_right

$SetAcquisitionFrequency1x,M,N : set the acquisition frequency of motor M for speed and position to 1 per encoder
                pulse if N=1 (default : 4 per encoder pulse if N=0)
                When using default parameter, acquisition are less frequent but more precise
                Useful especially for high speed movement.
                return values : none.

$MotorStop,M :  Turns motor M off.
                return values : none.

$MotorStart,M : Turns motor M on.
                return values : none.

$FollowLine,on,A,S : switch follow line on (or off if on=0) with speed = S and aggressivity=A

$AllowUDPUpdate,IP,port : signal he robot that it can open an udp socket for position update
                            from the computer that is connected to it
*/

void InitMap(){
    s_mapStringFunctions["GetID"] = &cmdGetID;
    s_mapStringFunctions["SetMode"] = &cmdSetMode;
    s_mapStringFunctions["GetMode"] = &cmdGetMode;
    s_mapStringFunctions["ResetPosition"] = &cmdResetPosition;
    s_mapStringFunctions["SetSpeed"] = &cmdSetSpeed;
    s_mapStringFunctions["SetPosition"] = &cmdSetPosition;
    s_mapStringFunctions["SetPoint"] = &cmdSetPoint;
    s_mapStringFunctions["RecordPulse"] = &cmdRecordPulse;
    s_mapStringFunctions["SetPID"] = &cmdSetPID;
    s_mapStringFunctions["GetPID"] = &cmdGetPID;
    s_mapStringFunctions["GetPosition"] = &cmdGetPosition;
    s_mapStringFunctions["GetSpeed"] = &cmdGetSpeed;
    s_mapStringFunctions["SetAcquisitionFrequency1x"] = &cmdSetAcquisitionFrequency1x;
    s_mapStringFunctions["MotorStop"] = &cmdMotorStop;
    s_mapStringFunctions["MotorStart"] = &cmdMotorStart;
    s_mapStringFunctions["GetInfraredAmbient"] = &cmdGetInfraredAmbient;
    s_mapStringFunctions["GetInfraredProximity"] = &cmdGetInfraredProximity;
    s_mapStringFunctions["GetUltrasound"]=&cmdGetUltraSound;
    s_mapStringFunctions["ResetIR"]=&cmdResetIR;
    s_mapStringFunctions["FollowLine"]=&cmdFollowLine;
    s_mapStringFunctions["AllowUDPUpdate"]=&cmdAllowUDPUpdate;
    s_mapStringFunctions["Cross"]=&cmdCross;
    s_mapStringFunctions["GripperGoTo"]=&cmdGripperGoTo;

    }

inline int i_ParseArguments(std::string cmd, int N, std::vector<unsigned int> *commapos){
    if (N<commapos->size()-1){
        return atoi(cmd.substr(commapos->at(N)+1,commapos->at(N+1)-commapos->at(N)-1).c_str());
    }
    else {
        return atoi(cmd.substr(commapos->at(N)+1,cmd.length()-commapos->at(N)-1).c_str());
    }
}

inline float f_ParseArguments(std::string cmd, int N, std::vector<unsigned int> *commapos){
    if (N<commapos->size()-1){
        return atof(cmd.substr(commapos->at(N)+1,commapos->at(N+1)-commapos->at(N)-1).c_str());
    }
    else {
        return atof(cmd.substr(commapos->at(N)+1,cmd.length()-commapos->at(N)-1).c_str());
    }
}
