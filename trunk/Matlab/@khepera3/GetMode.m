function modes = GetMode(k3)
modes = zeros(2,1);
left = libpointer('int32Ptr',0);
right = libpointer('int32Ptr',0);
calllib('khepera3clib', 'GetMode',k3.id,left,right);
modes(1) = get(left,'value')+1;
modes(2) = get(right,'value')+1;
end

