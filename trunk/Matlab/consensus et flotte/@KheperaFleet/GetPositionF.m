function [X Y] = GetPositionF(KheperaFleet)
X = zeros(KheperaFleet.NumberOfKhepera,1);
Y = zeros(KheperaFleet.NumberOfKhepera,1);
for i=1:KheperaFleet.NumberOfKhepera
    P = KheperaFleet.KheperaArray(i,1).GetXYPosition;
    X(i,1) = P(1);
    Y(i,1) = P(2);    
end

end