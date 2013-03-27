% function used by continuous acquisition only !
% lock is acquired by RunAcquisition

function pos = GetPosition(k3)
    pos = zeros(2,1); 
    left = libpointer('int32Ptr',0);
    right = libpointer('int32Ptr',0);
    %tic
    error = calllib('khepera3clib', 'GetEncoderPosition',k3.id,left,right);        
    if error
        ME = MException('GetPosition:CommunicationError', ...
             'The connection with the robot has failed. Check the network and try to reconnect');
        throw(ME);
    end
    %toc
    pos(1) = get(left,'value');
    pos(2) = get(right,'value');
    pos = khepera3.K3toRW(2,pos);
end

