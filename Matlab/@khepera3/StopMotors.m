function StopMotors(k3)
error = calllib('khepera3clib', 'StopMotors',k3.id); if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
end

