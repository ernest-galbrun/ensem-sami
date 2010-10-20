function error = Connect(k3,Id,localIP,varargin)
    % varargin{1} = handle to message string
    if nargin > 3
        h_message = varargin{1};
        set(h_message,'string','Trying to connect...');
    end
    drawnow update;
    error = 0;    
    if k3.id ~= 0
        k3.RunAcquisition('stop');
    %    fclose(k3.t);
    end
    %set(k3.t,'RemoteHost',hostIp);
    try
        %pp = libpointer('voidPtrPtr');
        Id=str2num(Id);
        calllib('khepera3clib','LaunchKhepera',Id);
        k3.id = Id;
        %k3.p = get(pp,'value');
        calllib('khepera3clib','InitLocalizationSystem',Id,1,localIP,'193.49.136.176');
        message = {'Connection established'};
        %fopen(k3.t);
        %if k3.lock(5)==0
        %    fprintf(k3.t,'$GetId');
        %    message = {'Connection established';['Robot Id : ' fscanf(k3.t)]};
        %    ok = fscanf(k3.t);
        %    fprintf(k3.t,'$SetAcquisitionFrequency1x,0,1');
        %    ok = fscanf(k3.t);
        %    fprintf(k3.t,'$SetAcquisitionFrequency1x,1,1');
        %    ok = fscanf(k3.t);
        %    k3.unlock();
        %else
        %    message = 'Connection failed';
        %end
    catch ME
        message = 'Connection failed';
        error = 1;
    end
    if nargin>3
        set(h_message,'string',message);
    end
end
