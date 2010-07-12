% function used by continuous acquisition only !
% lock is acquired by RunAcquisition

function pos = GetPosition(k3)
    fprintf(k3.t,'$GetPosition');
    pos = fscanf(k3.t,'%d,%d');
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'GetPosition')
        error('Transmission error position reading');
    end
    pos = khepera3.K3toRW(2,pos);
end

