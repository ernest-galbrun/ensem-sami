function modes = GetMode(k3)
if k3.lock(1)==0;
    fprintf(k3.t,'$GetMode');
    modes = fscanf(k3.t,'%d,%d');
    if modes(1)==255
        modes(1)=0;
    end
    if modes(2) == 255
        modes(2) = 0;
    end
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'GetMode')
        error('Transmission error during mode read');
    end
    modes = modes +1;
    k3.unlock();
end
end

