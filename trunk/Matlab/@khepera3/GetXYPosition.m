% get RW position

function pos = GetXYPosition(k3)
    x = libpointer('doublePtr',0);
    y = libpointer('doublePtr',0);
    error = calllib('khepera3clib', 'GetPosition',k3.id,x,y);
    if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
    end
    pos(1) = get(x,'value');
    pos(2) = get(y,'value');
end

