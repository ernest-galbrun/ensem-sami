function configDrone(port,altMax,eulerMax,yawMax)
%Gestion du sequence number
global sequenceNumber;
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:altitude_max","%d"\r',sequenceNumber,altMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*LED=%d,9,1056964608,4\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*FTRIM=%d\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:euler_angle_max","%d"\r',sequenceNumber,eulerMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:control_yaw","%d"\r',sequenceNumber,yawMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:altitude_max","%d"\r',sequenceNumber,altMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*LED=%d,9,1056964608,4\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*FTRIM=%d\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:euler_angle_max","%d"\r',sequenceNumber,eulerMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:control_yaw","%d"\r',sequenceNumber,yawMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:altitude_max","%d"\r',sequenceNumber,altMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*LED=%d,9,1056964608,4\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*FTRIM=%d\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:euler_angle_max","%d"\r',sequenceNumber,eulerMax));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*CONFIG=%d,"control:control_yaw","%d"\r',sequenceNumber,yawMax));
end