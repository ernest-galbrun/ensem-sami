function StartMotors(k3)
if (k3.lock()==0)
    fprintf(k3.t,('$MotorStart,0'));
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'MotorStart')
        error('Transmission error motor start');
    end      
    fprintf(k3.t,('$MotorStart,1'));
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'MotorStart')
        error('Transmission error motor start');
    end
    k3.unlock();
end
end