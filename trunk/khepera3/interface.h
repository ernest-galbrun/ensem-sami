#ifdef __cplusplus 
extern "C" {
#endif 
	// Connects to the robot 10.10.10.N
	//Creates KheperaIII object, returns a pointer to it
	__declspec(dllexport) int LaunchKhepera(int robotID, int mode, void** k3ptr);

	// Set speed for both motor (this changes the operating mode at every call, maybe
	// use SetMode then SetPoint for more efficient use)
	__declspec(dllexport) int SetSpeed(void* k3ptr, int left, int right);

	__declspec(dllexport) int InitLocalizationSystem(void* k3ptr, const char* localIP, const char* cortexIP);

	__declspec(dllexport) int GetPosition(void* agent_ptr, double* posLeft, double* posRight);

#ifdef __cplusplus
}
#endif