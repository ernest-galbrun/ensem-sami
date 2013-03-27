function DTLeft(k3,agressivity,velocity)
A=k3.GetOrientation;
B=A;
k3.StartMotors;
while A<B+3.14
    
	error = calllib('khepera3clib', 'SetSpeed',k3.id,0.5,0.7);
    if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
    end
	A=k3.GetOrientation;
end
	error = calllib('khepera3clib', 'StopMotors',k3.id);
    if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
    end
	k3.StartFollowLine(agressivity,velocity);
end