function SetConnectionModeF(KheperaFleet,mode)
% Sets the method for retrieving he position :
% 0 : offline
% 1 : online (uses position given by cortex
% 2 : offline with the initial position gieven by cortex
for i=1:KheperaFleet.NumberOfKhepera
   KheperaFleet.KheperaArray(i,1).SetConnectionMode(mode);
end