function SetPosition(k3,left,right)
if k3.lock()==0
    fprintf(k3.t,'$ResetPosition,%d,%d\n',khepera3.RWtoK3(2,[left right]));    
    str = fscanf(k3.t);    
    if ~strcmp(str(1:end-2),'ResetPosition')
        error('Transmission error mode change');
    end
    k3.unlock();
end

