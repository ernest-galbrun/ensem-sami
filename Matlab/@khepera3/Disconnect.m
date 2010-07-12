function Disconnect(k3)
if strcmp(k3.timerAcquisition.Running,'on')
    k3.RunAcquisition('stop');
    k3.unlock();
end

if strcmp(k3.t.status,'open')
    fclose(k3.t);
end


end

