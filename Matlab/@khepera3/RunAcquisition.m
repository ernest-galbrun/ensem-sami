function RunAcquisition(k3, mode)
% Start or stop continuous acquisition of position and speed
% h_array is an array of handles to the screen display
% mode = {'start'|'stop'})
    switch mode
        case 'start'
            start(k3.timerAcquisition);
             error = calllib('khepera3clib', 'StartInternalTracking',k3.id);
              if error
                ME = MException('GetPosition:CommunicationError', ...
                     'The connection with the robot has failed. Check the network and try to reconnect');
                throw(ME);
              end
        case 'stop'
            stop(k3.timerAcquisition);
            %error = calllib('khepera3clib', 'StopInternalTracking',k3.id);          
   
    end
end