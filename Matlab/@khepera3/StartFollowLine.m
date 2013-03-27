function StartFollowLine(k3,agressivity,velocity)

k3.StartMotors
error = calllib('khepera3clib','FollowLine',k3.id,true,agressivity,velocity);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end

end