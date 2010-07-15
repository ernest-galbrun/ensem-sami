classdef khepera3 < handle
    % k3 is the generic class containing khepera3 tcpip command functions
    % it is used in conjonction with the proper tcpip server program 
    % running on the robots
    
    properties (Access = public)
       
    end
    
    properties (Access = private) %t : handle to the tcpip object
        %p = libpointer('voidPtr');
        %t = tcpip('0.0.0.0',
        %14,'terminator','CR/LF','inputbuffersize',1000000);
        id = 0;
        busy = false;
        timerAcquisition = timer('Period',0.5,'ExecutionMode','fixedSpacing',...
                                 'BusyMode','drop','TasksToExecute',Inf);
    end
       
    methods (Access = public)
        % Constructor, specifying the handles to the position and speed
        % indicator on screen
        function k3 = khepera3(h_array)
            loadlibrary('khepera3clib.dll','khepera3clib.h');
            if nargin>0
                set(k3.timerAcquisition,'TimerFcn',{@CallBackAcquisition,k3,h_array});
            end
        end
        
        function delete(k3)
           %delete(k3.t);
            delete(k3.timerAcquisition);
        end
        
        % Start or stop continuous acquisition of position and speed
        % h_array is an array of handles to the screen display
        % mode = {'start'|'stop'}
        RunAcquisition(k3, mode)
        error = Connect(k3,Id,localIP,h_message)   
        Disconnect(k3)
        SetMode(k3,modeLeft,modeRight)
        modes = GetMode(k3)
        PID = GetPID(k3)
        SetPID(k3,PID)
        SetPoint(k3,targetLeft,targetRight)
        record = StepAcquisition(k3,stepData,acquisitionMode)
        SetPosition(k3,left,right);
        StopMotors(k3);
        StartMotors(k3);
        % Get motor positions directly from encoders values
        pos = GetPosition(k3);
        % Get XY position
        posXY = GetXYPosition(k3);
        orientation = GetOrientation(k3);
        SetVelocity(k3,lineraVelocity, angularVelocity);
    end
    
    methods (Access = private)
        % Acquire lock on the ressources
        % Return false if result is a success
        % Unlock resets busy to false and is always a success
        timeout = lock(k3,timeout_val)
        unlock(k3)     
    end    
    
    methods (Static)
        K3value = RWtoK3(mode, RWvalue);
        RWvalue = K3toRW(mode, k3value);
    end
end

function CallBackAcquisition (obj,event,k3, h_Array)
    pos = k3.GetPosition();
    speed = k3.GetSpeed();
    set(h_Array(1),'String',pos(1));
    set(h_Array(2),'String',pos(2));
    set(h_Array(3),'String',speed(1));
    set(h_Array(4),'String',speed(2));
end