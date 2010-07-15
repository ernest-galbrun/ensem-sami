function error = Connect(k3,hostIp,h_message)
    set(h_message,'string','Trying to connect...');
    drawnow update;
    error = 0;    
    if strcmp(get(k3.t,'status'),'open')
        k3.RunAcquisition('stop');
        fclose(k3.t);
    end
    set(k3.t,'RemoteHost',hostIp);
    try
        fopen(k3.t);
        if k3.lock(5)==0
            fprintf(k3.t,'$GetId');
            message = {'Connection established';['Robot Id : ' fscanf(k3.t)]};
            ok = fscanf(k3.t);
            fprintf(k3.t,'$SetAcquisitionFrequency1x,0,1');
            ok = fscanf(k3.t);
            fprintf(k3.t,'$SetAcquisitionFrequency1x,1,1');
            ok = fscanf(k3.t);
            k3.unlock();
        else
            message = 'Connection failed';
        end
    catch
        message = 'Connection failed';
        error = 1;
    end
    set(h_message,'string',message);
end

