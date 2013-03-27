function SetPoint(k3,targetLeft,targetRight)
error = calllib('khepera3clib', 'SetTargetPoint',k3.id, targetLeft, targetRight);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
end

