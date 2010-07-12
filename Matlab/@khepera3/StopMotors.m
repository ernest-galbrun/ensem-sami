function StopMotors(k3)
if (k3.lock()==0)
    fprintf(k3.t,('$MotorStop,0'));
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'MotorStop')
        error('Transmission error motor stop');
    end      
    fprintf(k3.t,('$MotorStop,1'));
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'MotorStop')
        error('Transmission error motor stop');
    end
    k3.unlock();
end
end

