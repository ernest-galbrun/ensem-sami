function timeout = lock(k3,timeout_val)
    tStart = tic;
    while(k3.busy == true && toc(tStart)<timeout_val)
        pause(0.01);
    end
    if k3.busy == false;
        timeout = false;
        k3.busy = true;
        return;
    else
        timeout = true;
        return
    end
end