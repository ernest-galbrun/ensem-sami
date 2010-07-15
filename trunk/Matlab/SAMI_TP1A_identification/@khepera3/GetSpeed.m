% function used by continuous acquisition only !
% lock is acquired by RunAcquisition
function speed = GetSpeed(k3)
    fprintf(k3.t,'$GetSpeed');
    speed = fscanf(k3.t,'%d,%d');
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'GetSpeed')
        error('Transmission error speed reading');
    end
    speed = khepera3.K3toRW(4,speed);
end

