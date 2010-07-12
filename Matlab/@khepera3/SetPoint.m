function SetPoint(k3,targetLeft,targetRight)
if k3.lock()==0
    fprintf(k3.t,'$SetPoint,%d,%d\n',[targetLeft targetRight]);
    str = fscanf(k3.t);  
    if ~strcmp(str(1:end-2),'SetPoint')
        error('Transmission error during target point setting');
    end
    k3.unlock();
end
end

