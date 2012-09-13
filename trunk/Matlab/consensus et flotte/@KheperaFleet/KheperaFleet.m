classdef KheperaFleet < handle

properties
    NumberOfKhepera;
    KheperaArray;
    Network;
    IP;
end



%-------------------------------Methods------------------------------------
methods
% Constructor--------------------------------------------------------------
function Fleet = KheperaFleet(NumberOfKhepera)
    IP = IPAdress;
    Fleet.NumberOfKhepera = NumberOfKhepera;
    for i = 1:Fleet.NumberOfKhepera
        temp(i,1) = khepera3();
    end
    Fleet.KheperaArray = temp;
    Fleet.Network = zeros(NumberOfKhepera,NumberOfKhepera);

end


% Declaration of other methods which will be detailled in other m-files ---
error=ConnectF(KheperaFleet,KheperaID,Virtual,InitialPosition,InitialOrientation);
DisconnectF(KheperaFleet,KheperaID);
[X Y] = GetPositionF(KheperaFleet);
Phi = GetOrientationF(KheperaFleet);
SetVelocityF(KheperaFleet,LinearVelocity,AngularVelocity);

DefineNetwork(KheperaFleet,varargin);

DisplayF(KheperaFleet,varargin);

RDV_Static(KheperaFleet,FinalRadius,tau,stop);
GoTo(KheperaFleet,FinalPosition,time,Plot,stop);
ChangeAngle(KheperaFleet,FinalAngle,Vlin);
FleetFormation(KheperaFleet,tau,kindofformation,parameters,stop);
ChangeAngleAndSpeed(KheperaFleet,FinalAngle,FinalVlin,time);
Flocking(KheperaFleet,Vlin,time);
end
%------------------------------End Methods---------------------------------



end