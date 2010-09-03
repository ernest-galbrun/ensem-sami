function DrawStep(h_stepPlot,stepData,result)
L_value = result(2,:);
R_value = result(3,:);
timestamp = result(1,:);
i=1;
L_target = [];
R_target = [];
while i<= length(stepData) && ~isempty(stepData{i,3})
    L_target = [L_target zeros(1,stepData{i,3}) + stepData{i,1}];
    R_target = [R_target zeros(1,stepData{i,3}) + stepData{i,2}];
    i=i+1;
end
plot(h_stepPlot,timestamp,[L_target;L_value;R_target;R_value]);
assignin('base','L_target',L_target);
assignin('base','R_target',R_target);
assignin('base','L_value',L_value);
assignin('base','R_value',R_value);
assignin('base','timestamp',timestamp);
end

