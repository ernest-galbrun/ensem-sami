function modes = GetMode(k3)
modes = zeros(2,1);
left = libpointer('int32Ptr',0);
right = libpointer('int32Ptr',0);
error = calllib('khepera3clib', 'GetMode',k3.id,left,right);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
modes(1) = get(left,'value')+1;
if (modes(1)==256)
    modes(1) = 1;
end
modes(2) = get(right,'value')+1;
if (modes(2)==256)
    modes(2) = 1;
end
end

