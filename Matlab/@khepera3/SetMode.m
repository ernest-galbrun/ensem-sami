function SetMode(k3,modeLeft,modeRight)
error = calllib('khepera3clib', 'SetMode',k3.id,modeLeft-1, modeRight-1);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
end

