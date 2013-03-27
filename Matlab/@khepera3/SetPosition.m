function SetPosition(k3,left,right)
error = calllib('khepera3clib', 'ResetPosition',k3.id,left,right);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
end

