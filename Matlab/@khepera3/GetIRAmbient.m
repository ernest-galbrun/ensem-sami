function [values timestamp] = GetIRAmbient(k3)
val = libpointer('int32PtrPtr');
timestamp = libpointer('int32Ptr',0);
error = calllib('khepera3clib','GetAmbientIR',k3.id,timestamp,val);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
val = get(val,'value');
setdatatype(val,'int32Ptr',11);
values = get(val,'value');
timestamp = get(timestamp,'value');
end

