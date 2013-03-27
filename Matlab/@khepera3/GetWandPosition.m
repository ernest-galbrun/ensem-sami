function pos = GetWandPosition(k3)
    pos = zeros(2,1); 
    X = libpointer('doublePtr',0);
    Y = libpointer('doublePtr',0);
    error = calllib('khepera3clib', 'GetWandPosition',X,Y);
    pos(1) = get(X,'value');
    pos(2) = get(Y,'value');
end

