function orientation = GetOrientation(k3)
    x = libpointer('doublePtr',0);
    calllib('khepera3clib', 'GetOrientation',x);
    orientation = get(x,'value');
end

