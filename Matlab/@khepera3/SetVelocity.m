function SetVelocity(k3,linearVelocity, angularVelocity)
%linearvelocity in cm/s
%angularvelocity in rad/s
error = calllib('khepera3clib', 'SetSpeed',k3.id,linearVelocity,angularVelocity);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
end

