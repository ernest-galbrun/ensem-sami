function values = GetUltrasound(k3)
val = libpointer('int32PtrPtr');
error = calllib('khepera3clib','GetUltrasound',k3.id,val);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
val = get(val,'value');
setdatatype(val,'int32Ptr',50);
values = get(val,'value');
values = reshape(values,10,5);
end

