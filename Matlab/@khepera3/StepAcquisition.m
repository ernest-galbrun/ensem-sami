function record = StepAcquisition(k3,stepData,acquisitionMode)
    modes = k3.GetMode();
    acquisitionMode = acquisitionMode -1;
if k3.lock() ==0
    n = 0;
    Nacquisition = 0;
    while n< length(stepData) && ~isempty(stepData{n+1,1})
        n=n+1;
        Nacquisition = Nacquisition + stepData{n,3};
    end
    stepData = stepData';
    for i=1:n
        stepData{1,i} = khepera3.RWtoK3(modes(1),stepData{1,i});
        stepData{2,i} = khepera3.RWtoK3(modes(2),stepData{2,i});    
    str = ['$RecordPulse' sprintf(',%d,%d', acquisitionMode)... 
            sprintf(',%d,%d,%d',stepData{:,1:n})];
    fprintf(k3.t,str);
    record = zeros(3,Nacquisition);
    for i=1:Nacquisition
        [record(:,i), count] = fscanf(k3.t,'%d,%d,%d');
    end
    str = fscanf(k3.t);
    if ~strcmp(str(1:end-2),'RecordPulse')
        error('Transmission error during pulse record');
    end
    k3.unlock();
    record(2,:)=khepera3.K3toRW(4,record(2,:));
    record(3,:)=khepera3.K3toRW(4,record(3,:));    
end
end

