function Cross(k3,direction,agressivity,velocity)

%k3.StartMotors
error = calllib('khepera3clib','Cross',k3.id,direction,agressivity,velocity);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end

end