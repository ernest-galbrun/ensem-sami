#ifdef __cplusplus 
extern "C" {
#endif 
	// Connects to the robot 10.10.10.N
	//Creates KheperaIII object, returns a pointer to it
	__declspec(dllexport) int LaunchKhepera(int robotID);

	// Set speed for both motor (this changes the operating mode at every call, maybe
	// use SetMode then SetPoint for more efficient use)
	__declspec(dllexport) int SetSpeed(double linear, double angular);

	__declspec(dllexport) int InitLocalizationSystem(int mode, const char* localIP, const char* cortexIP);

	__declspec(dllexport) int GetPosition(double* posX, double* posY);

	__declspec(dllexport) int GetOrientation(double* orientation);

#ifdef __cplusplus
}
#endif
