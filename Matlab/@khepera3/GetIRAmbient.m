function [values timestamp] = GetIRAmbient(k3)
val = libpointer('int32PtrPtr');
timestamp = libpointer('int32Ptr',0);
calllib('khepera3clib','GetAmbientIR',k3.id,timestamp,val);
val = get(val,'value');
setdatatype(val,'int32Ptr',11);
values = get(val,'value');
timestamp = get(timestamp,'value');
end

