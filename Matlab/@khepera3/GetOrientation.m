function orientation = GetOrientation(k3)
    x = libpointer('doublePtr',0);
    calllib('khepera3clib', 'GetOrientation',k3.id,x);
    orientation = get(x,'value');
end

