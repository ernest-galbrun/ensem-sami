function values = GetUltrasound(k3)
val = libpointer('int32PtrPtr');
calllib('khepera3clib','GetUltrasound',k3.id,val);
val = get(val,'value');
setdatatype(val,'int32Ptr',50);
values = get(val,'value');
values = reshape(values,10,5);
end

