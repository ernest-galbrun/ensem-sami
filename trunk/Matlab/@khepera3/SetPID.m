function SetPID(k3,PID)
mode = k3.GetMode();
if k3.lock()==0
    for i=1:2
        out = [i-1; PID(:,i)];
        switch mode(i)
            case 1 %open loop 
                str = 'SetPID..';
            case {2,3} %position
                fprintf(k3.t,'$SetPID,0,%d,%d,%d,%d\n',out);
                str = fscanf(k3.t);
            case {4,5} %speed
                fprintf(k3.t,'$SetPID,1,%d,%d,%d,%d\n',out);
                str = fscanf(k3.t);
            case 6 %Torque
                fprintf(k3.t,'$SetPID,2,%d,%d,%d,%d\n',out);
                str = fscanf(k3.t);
        end
        if ~strcmp(str(1:end-2),'SetPID')
            error('Transmission error during PID coefficient setting');
        end
    end
    k3.unlock();
end
end

