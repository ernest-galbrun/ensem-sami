function SetMode(k3,modeLeft,modeRight)
    k3.lock();
    fprintf(k3.t,'$SetMode,%d,%d\n',[modeLeft-1 modeRight-1]);
    str = fscanf(k3.t);    
    if ~strcmp(str(1:end-2),'SetMode')
        error('Transmission error mode change');
    end
    k3.unlock();
end

