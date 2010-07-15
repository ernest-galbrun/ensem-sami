function PID = GetPID(k3)
mode = k3.GetMode();
PID = zeros(2,3);
if k3.lock()==0
    for i=1:2
        switch mode(i)
            case 1 %open loop
                PID(i,:) = [0 0 0];
                str = 'GetPID..';
            case {2,3} %position
                fprintf(k3.t,'$GetPID,0,%d\n',i-1);
                PID(i,:)=fscanf(k3.t,'%d,%d,%d');
                str = fscanf(k3.t);
            case {4,5} %speed
                fprintf(k3.t,'$GetPID,1,%d\n',i-1);
                PID(i,:) = fscanf(k3.t,'%d,%d,%d');
                str = fscanf(k3.t);
            case 6 %Torque
                fprintf(k3.t,'$GetPID,2,%d\n',i-1);
                PID(i,:) = fscanf(k3.t,'%d,%d,%d');
                str = fscanf(k3.t);
        end
        if ~strcmp(str(1:end-2),'GetPID')
            error('Transmission error PID reading');
        end
    end
    k3.unlock();
end

end

