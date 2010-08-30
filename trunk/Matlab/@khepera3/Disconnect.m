function Disconnect(k3)
if strcmp(k3.timerAcquisition.Running,'on')
    k3.RunAcquisition('stop');
    k3.unlock();
end
end

