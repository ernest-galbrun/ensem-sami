% function used by continuous acquisition only !
% lock is acquired by RunAcquisition
function speed = GetSpeed(k3)
    speed = zeros(2,1);
    left = libpointer('int32Ptr',0);
    right = libpointer('int32Ptr',0);
    calllib('khepera3clib', 'GetSpeed',k3.id,left,right);
    speed(1) = get(left,'value');
    speed(2) = get(right,'value');
    speed = khepera3.K3toRW(4,speed);
end

