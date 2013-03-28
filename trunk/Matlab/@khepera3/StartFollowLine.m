function StartFollowLine(k3,aggressivity,velocity)

k3.StartMotors
%aggressivity = single(aggressivity);
error = calllib('khepera3clib','FollowLine',k3.id,true,aggressivity,velocity);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end

end