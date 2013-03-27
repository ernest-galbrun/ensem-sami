function SetPID(k3,PID)
PID = PID * 30800;
PID(2,:) = PID(2,:)/1000;
error = calllib('khepera3clib', 'SetPID',k3.id,PID(1,1),PID(2,1),PID(3,1),PID(1,2),PID(2,2),PID(3,2));
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
end

