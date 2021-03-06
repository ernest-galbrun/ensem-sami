function record = StepAcquisition(k3,stepData,acquisitionMode, controlModeLeft, controlModeRight)
N = 0;
Nacquisition = 0;
while(stepData(N+1,3)~=0)
    N = N+1;
    Nacquisition = Nacquisition + stepData(N,3);
end
timeStamp = libpointer('int32PtrPtr');
valuesLeft = libpointer('int32PtrPtr');
valuesRight = libpointer('int32PtrPtr');
targetLeft = khepera3.RWtoK3(controlModeLeft,stepData(1:N,1));
targetRight = khepera3.RWtoK3(controlModeRight,stepData(1:N,2));

error = calllib('khepera3clib', 'RecordPulse',k3.id, acquisitionMode(1)-1,acquisitionMode(2)-1, N,...
        targetLeft,targetRight,stepData(1:N,3),...
        timeStamp,valuesLeft,valuesRight);
     if error
        ME = MException('GetPosition:CommunicationError', ...
             'The connection with the robot has failed. Check the network and try to reconnect');
        throw(ME);
    end

record = zeros(3,Nacquisition);
A = get(timeStamp,'value');
B = get(valuesLeft,'value');
C = get(valuesRight,'value');
setdatatype(A,'int32Ptr',1,Nacquisition);
setdatatype(B,'int32Ptr',1,Nacquisition);
setdatatype(C,'int32Ptr',1,Nacquisition);
record(1,:) = get(A,'value');
record(2,:) = get(B,'value');
record(3,:) = get(C,'value');
record(2,:)=khepera3.K3toRW(4,record(2,:));
record(3,:)=khepera3.K3toRW(4,record(3,:)); 

end

