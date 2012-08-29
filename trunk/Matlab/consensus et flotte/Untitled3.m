% close all
% clear all
% clc
% R = KheperaFleet(3)
% R.ConnectF([10,11,12],[1,1,1],[0 0;0 150;0 300],[0.1;-2;3])
% R.DefineNetwork('manual',[0,1,0;1,0,1;0,1,0])
% Vmax = 100;
% R.GoTo(-[200 0;200 150;200 300],-1,1,1)

close all 
clear all
clc
A = [0 0 0;1 0 1;0 0 0]
A = A +A'
R = KheperaFleet(3);
e = R.ConnectF([1;4;7],[0,0,0],[0 0;0 1500;1800 1500],[3*pi/2;0;pi])
R.DefineNetwork('manual',A);
 
R.KheperaArray(1).StopMotors
R.KheperaArray(2).StopMotors
R.KheperaArray(3).StopMotors
[X Y] =R.GetPositionF
R.FleetFormation(-1,'line',[2 700],0)
R.Flocking(80*[1;1.1;1.2],1.5);
% R.ChangeAngleAndSpeed(0,0,4)
% R.GoTo([0000 00],-1,1,1);
R.SetVelocityF(0,0)
R.SetVelocityF(zeros(3,1),zeros(3,1))