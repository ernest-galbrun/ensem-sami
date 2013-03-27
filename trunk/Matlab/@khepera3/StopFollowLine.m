function StopFollowLine(k3)
error = calllib('khepera3clib','FollowLine',k3.id,false,0,0);
 if error
        ME = MException('GetPosition:CommunicationError', ...
             'The connection with the robot has failed. Check the network and try to reconnect');
        throw(ME);
    end
end