% get RW position

function pos = GetXYPosition(k3)
    x = libpointer('doublePtr',0);
    y = libpointer('doublePtr',0);
    calllib('khepera3clib', 'GetPosition',k3.id,x,y);
    pos(1) = get(x,'value');
    pos(2) = get(y,'value');
end

