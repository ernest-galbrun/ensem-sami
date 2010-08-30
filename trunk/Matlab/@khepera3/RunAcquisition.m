function RunAcquisition(k3, mode)
% Start or stop continuous acquisition of position and speed
% h_array is an array of handles to the screen display
% mode = {'start'|'stop'})
    switch mode
        case 'start'
            start(k3.timerAcquisition);
            calllib('khepera3clib', 'StartInternalTracking',k3.id);
        case 'stop'
            stop(k3.timerAcquisition);
            calllib('khepera3clib', 'StopInternalTracking',k3.id);            
    end
end