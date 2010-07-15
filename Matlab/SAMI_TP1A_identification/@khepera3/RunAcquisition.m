function RunAcquisition(k3, mode)
% Start or stop continuous acquisition of position and speed
% h_array is an array of handles to the screen display
% mode = {'start'|'stop'})
    switch mode
        case 'start'
            if k3.lock(1)==0
                start(k3.timerAcquisition);
            end
        case 'stop'
            stop(k3.timerAcquisition);
            k3.unlock();
    end
end