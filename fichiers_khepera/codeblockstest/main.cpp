#include "sami_tp1A.hpp"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <string>
#include <stdexcept>
# include <algorithm>
# include <ctime>
#include <sstream>
#include <fstream>
#include <cstdio>
#include "cyberglove_gripper.h"

#define USE_K3TB // for using epfl K3 toolbox
//#define USE_KT // for using k-team's libkorebot


#ifdef USE_K3TB
    #include "khepera3/khepera3.h"
    #include "commandline/commandline.h"
    #include "measurement/measurement.h"
#elif defined USE_KT
extern "C" {
    #include <korebot/korebot.h> //libkorebot
}
    #define MAXBUFFERSIZE 100
    static int quitReq = 0;
    static char buf[1024];
    /*! handle to the various khepera3 devices (knet socket, i2c mode)
     */
    static knet_dev_t * dsPic;
    static knet_dev_t * mot1;
    static knet_dev_t * mot2;
    kMotRegType regLeft = kMotRegOpenLoop;
    kMotRegType regRight = kMotRegOpenLoop;
#endif

using boost::asio::ip::tcp;
using namespace std;
using namespace boost;

mutex k3lock;
const int max_length = 1024;
const char* path_to_udp_server_description_file = "/home/root/udp_server";
struct UDPFile{
    ~UDPFile(){
        remove(path_to_udp_server_description_file);
    }
    void SetValues(const vector<float>& input){
        ofstream f(path_to_udp_server_description_file, ios_base::out | ios_base::trunc);
        for (int i=0;i<3;++i)
            f<<int(input[i])<<'.';
        f<<(int)input[3]<<'\n'<<(int)input[4];
    };
} myFile;
bool stop;
bool follow;

template<class T> void CheckInputSize(int mandatorySize, const vector<T>& input) {
    if (input.size() != mandatorySize){
        stringstream message;
        message<<"Wrong number of inputs, this function takes "<< mandatorySize << " inputs.";
        throw(invalid_argument(message.str()));
    }
}

int cmdAllowUDPUpdate(const std::vector<float>& input, socket_ptr sock){
    CheckInputSize<float>(5,input);
    //int ip_address = input[0];
    //int port_number = input[1];
    myFile.SetValues(input);
    return 0;
}

void CrossThread(const std::vector<float>& input, socket_ptr sock){
    CheckInputSize<float>(3,input);
    short unsigned int direction = (short unsigned int) input[0];
    int aggressivity,speed;
    aggressivity = int(input[1]);
    speed = int(input[2]);
    vector<float> followlineParameters(3);
    followlineParameters[0] = 1;
    followlineParameters[1] = aggressivity;
    followlineParameters[2] = speed;
    cout<<    followlineParameters[0]<< '\t'<<    followlineParameters[1] << '\t'<<     followlineParameters[2]<<'\n';
    cmdFollowLine(followlineParameters);
    int irLeft=0;
    int irRight=0;
    chrono::duration<double> timeout = chrono::seconds(30);
    chrono::system_clock::time_point start =  chrono::system_clock::now();
    cout<< "irLeft:"<<irLeft<<"\nirRight"<<irRight<<'\n';
    k3lock.unlock();
    bool cross_not_found;
    if (direction == 1 || direction==2){
        while(cross_not_found =(irLeft<3800 | irRight<3800) & (chrono::system_clock::now() - start < timeout)) {
            this_thread::sleep(posix_time::milliseconds(50));
            #ifdef USE_K3TB
            //khepera3_infrared_proximity();
            irLeft = khepera3.infrared_proximity.sensor[10];
            irRight = khepera3.infrared_proximity.sensor[9];
            cout<< "irLeft:"<<irLeft<<"\nirRight"<<irRight<<'\n';
            #endif
        }
        cout <<"cross section detected\n";
        follow = false;
            if (cross_not_found){
            return;
        }
    }

    k3lock.lock();
    #ifdef USE_K3TB
    switch (direction) {
        case 0:
        break;
        case 1:
        int posL_final, posL;
        #ifdef USE_K3TB
        khepera3_drive_set_speed_using_profile(4861,694);
        khepera3_drive_get_current_position();
        posL = khepera3.motor_left.current_position;
        posL_final = posL + (165*10.3);
        #elif defined USE_KT
        kmot_SetPoint(mot1,kMotRegSpeedProfile,4861);
        kmot_SetPoint(mot2,kMotRegSpeedProfile,694);
        #endif
        timeout = chrono::seconds(5);
        start =  chrono::system_clock::now();
        while (posL<posL_final & chrono::system_clock::now() - start < timeout) {
            //cout<< "posL:" <<posL<< "posL_final:"<<posL_final<<'\n';
            this_thread::sleep(posix_time::milliseconds(50));
            #ifdef USE_K3TB
            khepera3_drive_get_current_position();
            posL = khepera3.motor_left.current_position;
            #elif defined USE_KT
            #endif
        }
        #ifdef USE_K3TB
        khepera3_drive_set_speed_using_profile(0,0);
        #endif
        cmdFollowLine(followlineParameters);
        break;
        case 2:
        int posR_final, posR;
        #ifdef USE_K3TB
        khepera3_drive_set_speed_using_profile(694,4861);
        khepera3_drive_get_current_position();
        posR = khepera3.motor_right.current_position;
        posR_final = posR + (165*10.3);
        #elif defined USE_KT
        kmot_SetPoint(mot1,kMotRegSpeedProfile,694);
        kmot_SetPoint(mot2,kMotRegSpeedProfile,4861);
        #endif
        cout<< "posR:" <<posR<< "posR_final:"<<posR_final<<'\n';
        timeout = chrono::seconds(5);
        start =  chrono::system_clock::now();
        while (posR<posR_final & chrono::system_clock::now() - start < timeout) {
            this_thread::sleep(posix_time::milliseconds(50));
            #ifdef USE_K3TB
            khepera3_drive_get_current_position();
            posR = khepera3.motor_right.current_position;
            //cout<< "posR:" <<posR<< "posR_final:"<<posR_final<<'\n';
            #elif defined USE_KT
            #endif
        }
        #ifdef USE_K3TB
        khepera3_drive_set_speed_using_profile(0,0);
        #endif
        cmdFollowLine(followlineParameters);
        break;
        case 3:
        #ifdef USE_K3TB
        khepera3_drive_set_speed_using_profile(-3000,3000);
        khepera3_drive_get_current_position();
        posR = khepera3.motor_right.current_position;
        posR_final = posR + (141*10.3);
        #elif defined USE_KT
        kmot_SetPoint(mot1,kMotRegSpeedProfile,-3000);
        kmot_SetPoint(mot2,kMotRegSpeedProfile,3000);
        #endif
        cout<< "posR:" <<posR<< "posR_final:"<<posR_final<<'\n';
        timeout = chrono::seconds(5);
        start =  chrono::system_clock::now();
        while (posR<posR_final & chrono::system_clock::now() - start < timeout) {
            this_thread::sleep(posix_time::milliseconds(50));
            #ifdef USE_K3TB
            khepera3_drive_get_current_position();
            posR = khepera3.motor_right.current_position;
            //cout<< "posR:" <<posR<< "posR_final:"<<posR_final<<'\n';
            #elif defined USE_KT
            #endif
        }
        #ifdef USE_K3TB
        khepera3_drive_set_speed_using_profile(0,0);
        #endif
        cmdFollowLine(followlineParameters);
        break;
    }
    #endif
    k3lock.unlock();
    return;
}


int cmdGripperGoTo(const std::vector<float>& input, socket_ptr sock){
    CheckInputSize<float>(2,input);
    int position_arm = input[0];
    int position_gripper = input[1];
    //cout << "gripper: " << position_gripper << "arm: " << position_arm;
    UpdateGripperTarget(position_arm, position_gripper);
}


int cmdCross(const std::vector<float>& input, socket_ptr sock){
    k3lock.lock();
    boost::thread ct = boost::thread(boost::bind(CrossThread,input,sock));
    return 0;
}

int cmdResetIR(const std::vector<float>& input, socket_ptr sock){
    k3lock.lock();
    #ifdef USE_K3TB
    khepera3_infrared_init();
    #endif
    k3lock.unlock();
}

int cmdGetUltraSound(const std::vector<float>& input, socket_ptr sock){
    k3lock.lock();
    stringstream sdata_out;
    CheckInputSize<float>(0,input);
    for (int j=0;j<5;j++){
        #ifdef USE_K3TB
        sdata_out<<khepera3.ultrasound.sensor[j].echos_count<<',';
        #endif
        for (int i=0;i<3;++i) {
            #ifdef USE_K3TB
            sdata_out<<khepera3.ultrasound.sensor[j].distance[i]<<',';
            sdata_out<<khepera3.ultrasound.sensor[j].amplitude[i]<<',';
            sdata_out<<khepera3.ultrasound.sensor[j].timestamp[i]<<',';
            #endif
        }
    }
    k3lock.unlock();
    char comma;
    sdata_out>>comma;
    sdata_out<<"\r\n";
    sock->write_some(asio::buffer(sdata_out.str()));
    return(0);
}

int cmdGetInfraredAmbient(const std::vector<float>& input, socket_ptr sock){
    k3lock.lock();
    CheckInputSize<float>(0,input);
    stringstream sdata_out;
    #ifdef USE_K3TB
    khepera3_infrared_ambient();
    sdata_out<<khepera3.infrared_ambient.timestamp;
    for (int i=0;i<11;++i) {
        sdata_out<<','<<khepera3.infrared_ambient.sensor[i];
    }
    #endif
    k3lock.unlock();
    sdata_out<<"\r\n";
    sock->write_some(asio::buffer(sdata_out.str()));
    return(0);
}


int cmdGetInfraredProximity(const std::vector<float>& input, socket_ptr sock){
    k3lock.lock();
    CheckInputSize<float>(0,input);
    stringstream sdata_out;
    #ifdef USE_K3TB
    khepera3_infrared_proximity();
    sdata_out<<khepera3.infrared_proximity.timestamp;
    for (int i=0;i<11;++i) {
        sdata_out<<','<<khepera3.infrared_proximity.sensor[i];
    }
    #endif
    k3lock.unlock();
    sdata_out<<"\r\n";
    sock->write_some(asio::buffer(sdata_out.str()));
    return(0);
}

int cmdGetID(const vector<float>& input, socket_ptr sock){
    stringstream sdata_out;
    #ifdef USE_K3TB
    sdata_out<<khepera3.robot_id<<"\r\n";
    #elif defined USE_KT
    ifstream fid("/etc/khepera/robotid");
    int id;
    fid>>id;
    sdata_out<<id<<"\r\n";
    #endif
    sock->write_some(asio::buffer(sdata_out.str()));
    return(0);
}

int cmdSetMode(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    CheckInputSize<float>(2,input);
    #ifdef USE_K3TB
    eKhepera3MotorMode newMode;
    newMode = eKhepera3MotorMode(input[0]);
    khepera3_motor_write_register8(&(khepera3.motor_left), cKhepera3MotorRegister8_ControlType, newMode);
    newMode = eKhepera3MotorMode(input[1]);
    khepera3_motor_write_register8(&(khepera3.motor_right), cKhepera3MotorRegister8_ControlType, newMode);
    #elif defined USE_KT
    regLeft = kMotRegType(input[0]);
    regRight = kMotRegType(input[1]);
    #endif
    k3lock.unlock();
    return(0);
}

int cmdGetMode(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    stringstream sdata_out;
    unsigned int mode;
    #ifdef USE_K3TB
    khepera3_motor_read_register8_p(&(khepera3.motor_left),cKhepera3MotorRegister8_ControlType,&mode);
    #elif defined USE_KT
    mode = (unsigned int)regLeft;
    #endif
    sdata_out<<mode;
    #ifdef USE_K3TB
    khepera3_motor_read_register8_p(&(khepera3.motor_right),cKhepera3MotorRegister8_ControlType,&mode);
    #elif defined USE_KT
    mode = (unsigned int)regRight;
    #endif
    k3lock.unlock();
    sdata_out<<','<<mode<<"\r\n";
    sock->write_some(asio::buffer(sdata_out.str()));
    return(0);
}

int cmdResetPosition(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    #ifdef USE_K3TB
    khepera3_drive_set_current_position((int)input[0] * khepera3.motor_left.direction,(int)input[1] * khepera3.motor_right.direction);
    #elif defined USE_KT
     kmot_SetPosition(mot1,(long)input[0]);
     kmot_SetPosition(mot2,(long)input[1] );
    #endif
    k3lock.unlock();
    return(0);
}

int cmdSetSpeed(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    follow = false;
    #ifdef USE_K3TB
    khepera3_drive_set_speed_using_profile((int)input[0],(int)input[1]);
    #elif defined USE_KT
    kmot_SetPoint(mot1,kMotRegSpeedProfile,(long)input[0]);
    kmot_SetPoint(mot2,kMotRegSpeedProfile,(long)input[1]);
    #endif
    k3lock.unlock();
    return(0);
}

int cmdSetPosition(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    follow = false;
    #ifdef USE_K3TB
    khepera3_drive_goto_position((int)input[0] * khepera3.motor_left.direction,(int)input[1] * khepera3.motor_right.direction);
    #elif defined USE_KT
    kmot_SetPoint(mot1,kMotRegPosProfile,(long)input[0]);
    kmot_SetPoint(mot2,kMotRegPosProfile,(long)input[1]);
    #endif
    k3lock.unlock();
    return(0);
}

int cmdSetPoint(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    follow = false;
    #ifdef USE_K3TB
    khepera3_motor_write_register32(&(khepera3.motor_left), cKhepera3MotorRegister32_Setpoint, (int)input[0] * khepera3.motor_left.direction);
    khepera3_motor_write_register32(&(khepera3.motor_right), cKhepera3MotorRegister32_Setpoint, (int)input[1] * khepera3.motor_right.direction);
    #elif defined USE_KT
    kmot_SetPoint( mot1, regLeft, (int)input[0]);
    kmot_SetPoint( mot2, regRight, (int)input[1]);
    #endif
    k3lock.unlock();
    return(0);
}

int cmdRecordPulse(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    follow = false;
    stringstream sdata_out;
    posix_time::ptime timestamp_ref(posix_time::microsec_clock::local_time());
    int temp, temp2;
    temp = (int)input[0];
    temp2 = (int)input[1];
    vector<int> recordLTotal;
    vector<int> recordRTotal;
    vector<boost::posix_time::ptime> timestampTotal;
    for (int i=0;i<(int)(input.size() - 2)/3;i++){
        int setpointL =(int) input[i*3+2];
        int setpointR = (int)input[i*3+3];
        int N =(int) input[i*3+4];
        vector<int> recordL(N);
        vector<int> recordR(N);
        vector<boost::posix_time::ptime> timestamp(N);
        #ifdef USE_K3TB
        khepera3_drive_get_current_speed();
        khepera3_drive_get_current_position();
        #endif
        if (temp!=0) {
            #ifdef USE_K3TB
            recordL[0] = (temp==1)?khepera3.motor_left.current_position:khepera3.motor_left.current_speed;
            #endif
        }
        if (temp2!=0) {
            #ifdef USE_K3TB
            recordR[0] = (temp2==1)?khepera3.motor_right.current_position:khepera3.motor_right.current_speed;
            #endif
        }
        timestamp[0] = posix_time::microsec_clock::local_time();
        #ifdef USE_K3TB
        khepera3_motor_write_register32(&(khepera3.motor_left), cKhepera3MotorRegister32_Setpoint, setpointL * khepera3.motor_left.direction);
        khepera3_motor_write_register32(&(khepera3.motor_right), cKhepera3MotorRegister32_Setpoint, setpointR * khepera3.motor_right.direction);
        #endif
        for (int i=1;i<N;i++){
            if (temp!=0){
                if (temp ==1){
                    #ifdef USE_K3TB
                    khepera3_motor_get_current_position(&(khepera3.motor_left));
                    recordL[i] = khepera3.motor_left.current_position;
                    #endif
                }
                else if (temp == 2){
                    #ifdef USE_K3TB
                    khepera3_motor_get_current_speed(&(khepera3.motor_left));
                    recordL[i] = khepera3.motor_left.current_speed;
                    #endif
                }
            }
            if (temp2 !=0){
                if (temp2 ==1){
                    #ifdef USE_K3TB
                    khepera3_motor_get_current_position(&(khepera3.motor_right));
                    recordR[i] = khepera3.motor_right.current_position;
                    #endif
                }
                else if (temp2 == 2){
                    #ifdef USE_K3TB
                    khepera3_motor_get_current_speed(&(khepera3.motor_right));
                    recordR[i] = khepera3.motor_right.current_speed;
                    #endif
                }
            }
            timestamp[i] = posix_time::microsec_clock::local_time();
        }
        recordLTotal.insert(recordLTotal.end(),recordL.begin(),recordL.end());
        recordRTotal.insert(recordRTotal.end(),recordR.begin(),recordR.end());
        timestampTotal.insert(timestampTotal.end(),timestamp.begin(),timestamp.end());
    }

    for(int i=0;i<timestampTotal.size();i++) {
        sdata_out<<(timestampTotal[i]-timestamp_ref).boost::posix_time::time_duration::total_microseconds()<<','<<recordLTotal[i]<<','<<recordRTotal[i]<<"\r\n";
        sock->write_some(asio::buffer(sdata_out.str()));
        sdata_out.str("");
    }
    #ifdef USE_K3TB
    khepera3_motor_write_register32(&khepera3.motor_left, cKhepera3MotorRegister32_Setpoint, 0);
    khepera3_motor_write_register32(&khepera3.motor_right, cKhepera3MotorRegister32_Setpoint, 0);
    #endif
    k3lock.unlock();
    return 0;
}


int cmdSetPID(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    #ifdef USE_K3TB
    sKhepera3Motor  *targetMotor;
    eKhepera3MotorRegister16 P,I,D;
    targetMotor = input[1] == 0?&khepera3.motor_left:&khepera3.motor_right;
    #elif defined USE_KT
    knet_dev_t * targetMotor = input[1] == 0?mot1:mot2;
    int regType;
    #endif
    unsigned int mode;
    mode = (unsigned int)input[0];
    switch (mode) {
        case 0:
        #ifdef USE_K3TB
        P = cKhepera3MotorRegister16_KpPosition;
        I = cKhepera3MotorRegister16_KiPosition;
        D = cKhepera3MotorRegister16_KdPosition;
        #elif defined USE_KT
        regType = kMotRegPos;
        #endif
        break;
        case 1:
        #ifdef USE_K3TB
        P = cKhepera3MotorRegister16_KpSpeed;
        I = cKhepera3MotorRegister16_KiSpeed;
        D = cKhepera3MotorRegister16_KdSpeed;
        #elif defined USE_KT
        regType = kMotRegSpeed;
        #endif
        break;
        case 2:
        #ifdef USE_K3TB
        P = cKhepera3MotorRegister16_KpTorque;
        I = cKhepera3MotorRegister16_KiTorque;
        D = cKhepera3MotorRegister16_KdTorque;
        #elif defined USE_KT
        regType = kMotRegTorque;
        #endif
        break;
    }
    #ifdef USE_K3TB
    khepera3_motor_write_register16(targetMotor, P, (int)input[2]);
    khepera3_motor_write_register16(targetMotor, I, (int)input[3]);
    khepera3_motor_write_register16(targetMotor, D, (int)input[4]);
    #elif defined SE_KT
    kmot_ConfigurePID( targetMotor, regType ,(int16_t) input[2] , (int16_t) input[3] , (int16_t) input[4] );
    #endif
    k3lock.unlock();
    return 0;
}

#ifdef USE_KT
void kmot_GetPID( knet_dev_t * dev ,
			int regtype ,
			uint16_t* Kp , uint16_t* Kd , uint16_t* Ki )
{
  unsigned char regs[3];

  switch(regtype) {

    /* Position */
  case kMotRegPos:
    regs[0] = MOT_KpPosL;
    regs[1] = MOT_KdPosL;
    regs[2] = MOT_KiPosL;
    break;

  case kMotRegPosProfile:   /* PosProfile   */
  case kMotRegSpeed:        /* Speed        */
  case kMotRegSpeedProfile: /* SpeedProfile */

    regs[0] = MOT_KpSpeedL;
    regs[1] = MOT_KdSpeedL;
    regs[2] = MOT_KiSpeedL;
    break;

  case kMotRegTorque: /* Current */
    regs[0] = MOT_KpTorqueL;
    regs[1] = MOT_KdTorqueL;
    regs[2] = MOT_KiTorqueL;
    break;
  }

  knet_set_order( dev , KMOT_ORDER_MASK );

  knet_read16( dev , regs[0] , Kp );
  knet_read16( dev , regs[1] , Kd );
  knet_read16( dev , regs[2] , Ki );
}
#endif

int cmdGetPID(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    CheckInputSize<float>(2,input);
    #ifdef USE_K3TB
    unsigned int mode,p_in, i_in, d_in;
    eKhepera3MotorRegister16 P,I,D;
    sKhepera3Motor  *targetMotor;
    targetMotor = input[1] == 0?&khepera3.motor_left:&khepera3.motor_right;
    #elif defined USE_KT
    knet_dev_t * targetMotor = input[1] == 0?mot1:mot2;
    int regType;
    unsigned short mode,p_in, i_in, d_in;
    #endif
    stringstream sdata_out;
    mode = (int)input[0];
    switch (mode) {
        case 0:
        #ifdef USE_K3TB
        P = cKhepera3MotorRegister16_KpPosition;
        I = cKhepera3MotorRegister16_KiPosition;
        D = cKhepera3MotorRegister16_KdPosition;
        #elif defined USE_KT
        regType = kMotRegPos;
        #endif
        break;
        case 1:
        #ifdef USE_K3TB
        P = cKhepera3MotorRegister16_KpSpeed;
        I = cKhepera3MotorRegister16_KiSpeed;
        D = cKhepera3MotorRegister16_KdSpeed;
        #elif defined USE_KT
        regType = kMotRegSpeed;
        #endif
        break;
        case 2:
        #ifdef USE_K3TB
        P = cKhepera3MotorRegister16_KpTorque;
        I = cKhepera3MotorRegister16_KiTorque;
        D = cKhepera3MotorRegister16_KdTorque;
        #elif defined USE_KT
        regType = kMotRegTorque;
        #endif
        break;
    }
    #ifdef USE_K3TB
    khepera3_motor_read_register16_p(targetMotor, P, &p_in);
    khepera3_motor_read_register16_p(targetMotor, I, &i_in);
    khepera3_motor_read_register16_p(targetMotor, D, &d_in);
    #elif defined USE_KT
    kmot_GetPID(targetMotor,regType,&p_in,&i_in,&d_in);
    #endif
    sdata_out<<p_in<<','<<i_in<<','<<d_in<<"\r\n";
    sock->write_some(asio::buffer(sdata_out.str()));
    sdata_out.str("");
    k3lock.unlock();
    return 0;
}

int cmdGetPosition(const vector<float>& input, socket_ptr sock){
    stringstream sdata_out;
    k3lock.lock();
    #ifdef USE_K3TB
   // cout<<"fetching positions\n";
    khepera3_drive_get_current_position();
    //cout<<"done fetching positions\n";
    sdata_out<<khepera3.motor_left.current_position<<','<<khepera3.motor_right.current_position<<"\r\n";
    #elif defined USE_KT
    unsigned int left,right;
      left = kmot_GetMeasure( mot1 , kMotRegPos );
      right = kmot_GetMeasure( mot2 , kMotRegPos );
      sdata_out<<left<<','<<right<<"\r\n";
    #endif
    k3lock.unlock();
    sock->write_some(asio::buffer(sdata_out.str()));
    sdata_out.str("");
    return 0;
}

int cmdGetSpeed(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    stringstream sdata_out;
    #ifdef USE_K3TB
    khepera3_drive_get_current_speed();
    sdata_out<<khepera3.motor_left.current_speed<<','<<khepera3.motor_right.current_speed<<"\r\n";
    #elif defined USE_KT
    sdata_out<<0<<','<<0<<"\r\n";
    #endif
    k3lock.unlock();
    sock->write_some(asio::buffer(sdata_out.str()));
    sdata_out.str("");
    return 0;
}

int cmdSetAcquisitionFrequency1x(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    //cout << input[0] << ' ' << input[1] << '\n';
    #ifdef USE_K3TB
    unsigned int temp,temp2;
    sKhepera3Motor  *targetMotor;
    targetMotor = input[0] == 0?&khepera3.motor_left:&khepera3.motor_right;
    khepera3_motor_read_register8_p(targetMotor, cKhepera3MotorRegister8_HardwareOptions, &temp);
    temp2 = cKhepera3MotorHardwareOptions_EncoderResolution;
    if (input[1]==1) {
        temp |= temp2;
        }
    else{
        ~temp2;
        temp &= temp2;
    }
    khepera3_motor_write_register8(targetMotor,cKhepera3MotorRegister8_HardwareOptions,temp);
    #elif defined USE_KT
    knet_dev_t * targetMotor = input[1] == 0?mot1:mot2;
    uint8_t opt;
    knet_read8(targetMotor,MOT_HWOptions ,&opt);
    knet_write8( targetMotor ,MOT_HWOptions,  opt|kMotHWOptEncRes1x);
    #endif
    k3lock.unlock();
    return 0;
}

int cmdMotorStop(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    follow = false;
    #ifdef USE_K3TB
    sKhepera3Motor  *targetMotor;
    targetMotor = input[0] == 0?&khepera3.motor_left:&khepera3.motor_right;
    khepera3_motor_stop(targetMotor);
    #elif defined USE_KT
    cout<<"motor id :"<<input[0]<<'\n';
    knet_dev_t * targetMotor = input[0] == 0?mot1:mot2;
    knet_write8( targetMotor , MOT_Mode , kMotModeIdle );
    #endif
    k3lock.unlock();
    return 0;
}

int cmdMotorStart(const vector<float>& input, socket_ptr sock){
    k3lock.lock();
    follow = false;
    #ifdef USE_K3TB
    sKhepera3Motor  *targetMotor;
    targetMotor = input[0] == 0?&khepera3.motor_left:&khepera3.motor_right;
    khepera3_motor_start(targetMotor);
    #elif defined USE_KT
    knet_dev_t * targetMotor = input[0] == 0?mot1:mot2;
    knet_write8( targetMotor , MOT_Mode , kMotModeNormal );
    #endif
    k3lock.unlock();
    return 0;
}

void Followline( int aggressivity, int speed){
    while(follow){
        // Get new IR proximity values
        k3lock.lock();
        #ifdef USE_K3TB
        khepera3_infrared_proximity();
        #endif
        // Calculate the speed difference
        int speeddiff = 0;
        #ifdef USE_K3TB
        speeddiff += khepera3.infrared_proximity.sensor[cKhepera3SensorsInfrared_FloorLeft] * aggressivity;
        speeddiff -= khepera3.infrared_proximity.sensor[cKhepera3SensorsInfrared_FloorRight] * aggressivity;
        #endif
        int max_IR = 0;
        for (int i=0;i<8;++i){
            #ifdef USE_K3TB
            max_IR = max(max_IR,khepera3.infrared_proximity.sensor[i]);
            #endif
        }
        if (max_IR<400) {
            // Set the speed
            #ifdef USE_K3TB
            khepera3_drive_set_speed(speed - speeddiff, speed + speeddiff);
            #endif
        }
        else {
            #ifdef USE_K3TB
            khepera3_drive_set_speed(0,0);
            #endif
        }
        k3lock.unlock();
        usleep(50000);
    }
    #ifdef USE_K3TB
    k3lock.lock();
    khepera3_drive_set_speed_using_profile(0,0);
    k3lock.unlock();
    #endif
}

int cmdFollowLine(const vector<float>& input, socket_ptr sock/* = socket_ptr()*/){
    int aggressivity,speed;
    bool go = bool(input[0]);
    aggressivity = int(input[1]);
    cout<<"agressivity"<<aggressivity<<'\n';
    speed = int(input[2]);
    if (go) {
        if (!follow) {
        follow = true;
        cout << "starting follow line\n";
        thread thread_follow(bind(Followline,aggressivity,speed));
        }
    }
    else {
        follow = false;
    }
}
 #ifdef USE_KT
/*--------------------------------------------------------------------*/
/*! initMot initializes then configures the motor control
 * unit.
 *
 * \param hDev device handle
 * \return A value :
 *      - 1 if success
 *      - 0 if any error
 *
 */
int initMot(knet_dev_t *hDev)
{
  if(hDev)
  {
	  kmot_SetMode( hDev , kMotModeIdle );
	  kmot_SetSampleTime( hDev , 1550 );
	  kmot_SetMargin( hDev , 6 );
	  if(hDev == mot1)
	    kmot_SetOptions( hDev , 0x0 , kMotSWOptWindup | kMotSWOptStopMotorBlk | kMotSWOptDirectionInv);
	  else
	    kmot_SetOptions( hDev , 0x0 , kMotSWOptWindup | kMotSWOptStopMotorBlk );
	  kmot_ResetError( hDev );
	  kmot_SetBlockedTime( hDev , 10 );
	  kmot_SetLimits( hDev , kMotRegCurrent , 0 , 500 );
	  kmot_SetLimits( hDev , kMotRegPos , -10000 , 10000 );

	  /* PID  */
	  kmot_ConfigurePID( hDev , kMotRegSpeed , 620, 3 , 10 );
	  kmot_ConfigurePID( hDev,kMotRegPos,600,20,30);
	  kmot_SetSpeedProfile(hDev,15000,30);

	  return 1;
  }
  else
  {
	  cout<<"initMot error, handle cannot be null\r\n";
	  return 0;
  }
}
#endif

int ProcessCommand(string cmd, socket_ptr sock) {
    string::iterator first,last;
    stringstream sdata_out;
    boost::system::error_code error;
    string cmdType = cmd.substr(0,cmd.find(','));
    if (cmdType!="GetPosition" && cmdType!="GetSpeed" ) {
    cout<<cmdType<<'\n';
    }
    vector<size_t> commapos;
    vector<float>  inputArguments;
    size_t pos = 0;
    // record the position of the commas for argument parsing
    // store each argument in inputArguments[]
    while (cmd.find(',',pos)!=cmd.npos){
        commapos.push_back(cmd.find(',',pos));
        pos = cmd.find(',',pos) + 1;
    }
    for (int i=0;i<(int)commapos.size();++i) {
        inputArguments.push_back(f_ParseArguments(cmd,i,&commapos));
    }

    if (s_mapStringFunctions.find(cmdType) != s_mapStringFunctions.end()) {
        try {
            s_mapStringFunctions[cmdType](inputArguments, sock);
        }
        catch (invalid_argument& e) {
            sdata_out<<e.what()<<"\r\n";
            sock->write_some(asio::buffer(sdata_out.str()));
            sdata_out.str("");
            cerr<<e.what();
        }
    }
    else {
        return -1;
    }
    //cout<<"done processing command\n";
    sdata_out<<cmdType<<"\r\n";
            boost::chrono::high_resolution_clock::time_point start;
            start = boost::chrono::high_resolution_clock::now();
    sock->write_some(asio::buffer(sdata_out.str()));
    boost::chrono::duration<double> sec = boost::chrono::high_resolution_clock::now() - start;
    //std::cout << "writing took " << sec.count() << " seconds\n";
    sdata_out.str("");
    return 0;
}


void session(socket_ptr sock)
{
    cout<<"beginning communication\n";
  try
  {

    boost::asio::ip::tcp::no_delay option(true);
    sock->set_option(option);
    const string crlf("\r\n");
    string cmdbuf,cmd;
    for (;;)
    {
      boost::chrono::high_resolution_clock::time_point start;
      char data[max_length];
      //string data;
      //data.resize(max_length);
      boost::system::error_code error;
      start = boost::chrono::high_resolution_clock::now();
      size_t length = sock->read_some(boost::asio::buffer(data, max_length), error);
      boost::chrono::duration<double> sec = boost::chrono::high_resolution_clock::now() - start;
      //std::cout << "reading took " << sec.count() << " seconds\n";

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
        //cmdbuf.append(data.begin(),data.end());
        cmdbuf.append(data,length);
      while (cmdbuf.find('$')!=cmdbuf.npos && cmdbuf.find(crlf)!=cmdbuf.npos)
      {
          cmd = cmdbuf.substr(cmdbuf.find('$')+1, cmdbuf.find(crlf) - cmdbuf.find('$') - 1 );
          cmdbuf = cmdbuf.substr(cmdbuf.find('$'), cmdbuf.size()-cmdbuf.find('$'));
          cmdbuf = cmdbuf.substr(cmdbuf.find(crlf)+1,cmdbuf.size()-cmdbuf.find(crlf));
         // start = boost::chrono::high_resolution_clock::now();
          ProcessCommand(cmd, sock);
            //boost::chrono::duration<double> sec = boost::chrono::high_resolution_clock::now() - start;
          //  std::cout << "took " << sec.count() << " seconds\n";
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
  remove(path_to_udp_server_description_file);
}

void server(boost::asio::io_service& io_service, short port)
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    cout<<"opening incoming socket\n";
    boost::asio::ip::tcp::socket socket(io_service);
    socket_ptr sock(new tcp::socket(io_service));
    a.accept(*sock);
    boost::thread t(boost::bind(session, sock));
  }
}

void ContinuousUltrasoundAcquisition(){
 while(!stop) {
    k3lock.lock();
     for (int i=0;i<5;i++) {
        #ifdef USE_K3TB
        khepera3_ultrasound(eKhepera3SensorsUltrasound(i));
        #endif
     }
    k3lock.unlock();
     boost::this_thread::sleep(boost::posix_time::millisec(100));
 }
}

int main(int argc, char* argv[])
{
  stop = false;
  InitMap();
  #ifdef USE_KT
    k3lock.lock();
  kh3_init();
  dsPic = knet_open( "Khepera3:dsPic" , KNET_BUS_I2C , 0 , NULL );
  mot1  = knet_open( "Khepera3:mot1" , KNET_BUS_I2C , 0 , NULL );
  mot2  = knet_open( "Khepera3:mot2" , KNET_BUS_I2C , 0 , NULL );
  cout<<"dsPic: "<<dsPic<<"\nmot1: "<<mot1<<"\nmot2: "<<mot2<<'\n';
  if(dsPic!=0)  {
    if((mot1!=0)&&(mot2!=0))    {
      initMot(mot1);
      initMot(mot2);
      //return 0;
    } else
      return -1;
  } else
    return -2;

  kmot_SetSpeedProfile( mot1, 15000 , 30);
  kmot_SetSpeedProfile( mot2, 15000 , 30);
  #endif
  #ifdef USE_K3TB
  khepera3_init();
  khepera3_motor_initialize(&(khepera3.motor_left));
  khepera3_motor_initialize(&(khepera3.motor_right));
  khepera3_drive_start();
  khepera3_ultrasound_init();
  #endif
    k3lock.unlock();
  //cout<<khepera3_ultrasound_set_max_echo_number(3);
  //cout<<khepera3_ultrasound_enable(cKhepera3SensorsUltrasoundBit_All);
  //boost::thread us(&ContinuousUltrasoundAcquisition);
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }
    cout<<"launching server\n";
    boost::asio::io_service io_service;
    server(io_service, atoi(argv[1]));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  stop = true;
  //us.join();
  return 0;
}

