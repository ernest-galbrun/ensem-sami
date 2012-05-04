function error = Connect(k3,Id,virtual,initialPosition, initialOrientation,varargin)
    % varargin{1} = handle to message string
    if nargin >= 6
        h_message = varargin{1};
        set(h_message,'string','Trying to connect...');
    end
    if nargin<5
        initialOrientation = 0;
    end
    if nargin<4
        initialPosition = [0 0];
    end
    if nargin<3
        virtual = 0;
    end
    isVirtual = virtual;
    drawnow update;
    if k3.id ~= 0
        k3.RunAcquisition('stop');
    %    fclose(k3.t);
    end
    %set(k3.t,'RemoteHost',hostIp);
    try
        %pp = libpointer('voidPtrPtr');
    if ischar(Id)
        Id=str2num(Id);
    end
        error = calllib('khepera3clib','LaunchKhepera',Id,isVirtual,...
            initialPosition(1),initialPosition(2),initialOrientation(1));
        if error~=0
            throw('Khepera:ConnectionFailure', 'Error number %d while calling LaunchKhepera',...
                error);
        end
        k3.id = Id;
        %k3.p = get(pp,'value'); 
        %CONNECTION MODE ONLINE
        %error = calllib('khepera3clib','InitLocalizationSystem',Id,1);
        %CONNECTION MODE ONLINE
        %error = calllib('khepera3clib','InitLocalizationSystem',Id,1);
        %CONNECTION MODE OFFLINE
       % error = calllib('khepera3clib','InitLocalizationSystem',Id,0);
       %CONNECTION MODE ONLINE FOR INITIAL POSITION ONLY
       error = calllib('khepera3clib','InitLocalizationSystem',Id,2);
        if error == 2
            message = {'Offline mode'};
        elseif error~=0
            message = {'Connection failed'};
        else
            message = {'Connection established'};
        end
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
    catch ME
        message = 'Connection failed';
        error = 1;
    end
    if nargin>5
        set(h_message,'string',message);
    end
end

