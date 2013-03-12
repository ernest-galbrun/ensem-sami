function PID = GetPID(k3)

    pLeft = libpointer('int32Ptr',0);
    iLeft = libpointer('int32Ptr',0);
    dLeft = libpointer('int32Ptr',0);
    pRight = libpointer('int32Ptr',0);
    iRight = libpointer('int32Ptr',0);
    dRight = libpointer('int32Ptr',0);
    calllib('khepera3clib', 'GetPID',k3.id,pLeft,iLeft,dLeft,pRight,iRight,dRight);
    PID = zeros(2,3);
    PID(1,1) = get(pLeft,'value');
    PID(1,2) = get(iLeft,'value');
    PID(1,3) = get(dLeft,'value');
    PID(2,1) = get(pRight,'value');
    PID(2,2) = get(iRight,'value');
    PID(2,3) = get(dRight,'value');
    PID = PID/30800;
    PID(:,:) = PID(:,:) * 1000;
end

