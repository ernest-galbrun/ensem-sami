#ifdef __cplusplus 
extern "C" {
#endif 
	// Connects to the robot 10.10.10.N
	//Creates KheperaIII object, returns a pointer to it
	__declspec(dllexport) int LaunchKhepera(int robotID, int isVirtual);

	// Delete robot
	__declspec(dllexport) int DeleteKhepera(int robotID);

	__declspec(dllexport) int SendPosition(int robotID);

	// Set speed for both motor (this changes the operating mode at every call, maybe
	// use SetMode then SetPoint for more efficient use)
	__declspec(dllexport) int SetSpeed(int robotID, double linear, double angular);

	// Launch the localization system in hybrid mode
	__declspec(dllexport) int InitLocalizationSystem(int robotID, int mode, const char* localIP, const char* cortexIP);

	// Get the position of the robot in cm, real coordinates
	__declspec(dllexport) int GetPosition(int robotID, double* posX, double* posY);

	// Get Absolute orientation
	__declspec(dllexport) int GetOrientation(int robotID, double* orientation);

	// Get the functionning mode of the motors :	0 : Open Loop
	//												1 : Position 
	//												2 : Position using acceleration
	//												3 : Speed
	//												4 : Speed using acceleration profile
	//												5 : Torque
	__declspec(dllexport) int GetMode(int robotID, int* modeLeft, int* modeRight);

	// Get PID values for both motors for the current mode
	__declspec(dllexport) int GetPID(int robotID, int* pLeft, int* iLeft, int* dLeft, int* pRight, int* iRight, int* dRight);

	// Get motor position in encoder value converted from the direct read of the encoder (different than the robot position)
	__declspec(dllexport) int GetEncoderPosition(int robotID, int* left, int* right);

	// Get speed of both wheels, in encoder unit
	__declspec(dllexport) int GetSpeed(int robotID, int* left, int* right);

	// Set functionning mode for both motor
	__declspec(dllexport) int SetMode(int robotID, int left, int right);

	// Set PID values
	__declspec(dllexport) int SetPID(int robotID, int pLeft, int iLeft, int dLeft, int pRight, int iRight, int dRight);

	// Give a target for both motor, in the currrent mode
	__declspec(dllexport) int SetTargetPoint(int robotID, int targetLeft, int targetRight);

	// Reset encoder position inside the robot motor controller
	__declspec(dllexport) int ResetPosition(int robotID, int posLeft, int posRight);

	// Start and stop motors
	__declspec(dllexport) int StartMotors(int robotID);
	__declspec(dllexport) int StopMotors(int robotID);

	// Record a step for both motors
	__declspec(dllexport) int RecordPulse(int robotID, int modeLeft, int modeRight, int nStep, int* targetLeft, int* targetRight, int* NAcquisition,
										  int** timeStamp, int** valuesLeft, int** valuesRight); 

	__declspec(dllexport) int StartInternalTracking(int robotID);
	__declspec(dllexport) int StopInternalTracking(int robotID);

	__declspec(dllexport) int GetNeighbors(int robotID, int* numberOfNeighbors, int** id, double** x, double** y);


#ifdef __cplusplus
}
#endif
