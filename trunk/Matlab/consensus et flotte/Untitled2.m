% Test RDV

clear all
close all
clc 
% A = sparse(5,5);
% A(1,2) = 1;
% A(1,5) = 1;
% A(2,3) = 1;
% A(4,5) = 1;
% A(2,5) = 1;
% A = A+A';
% A = full(A);
Ip = '193.49.136.188';
% R = KheperaFleet(5,Ip);
% R.ConnectF([10,11,12,13,14,15],[1,1,1,1,1,1],-1000+2000*rand(5,2),[0;pi;pi/2;3*pi/4;5*pi/6;8*pi/9])
% R.DefineNetwork('manual',A)
% % R.Flocking(80*[1;1.5;1.2;1.2;0.8],1.5);
% 
% % 
% % R.RDV_Static(10,0.5,0)
% R.FleetFormation(2,'line',[2 1000],0)
% R.FleetFormation(1,'circle',1000,0)

% R = KheperaFleet(5)
% A = [0 1 0 1 0 ;0 0 1 0 0;0 0 0 1 0;0 0 0 0 1;0 0 0 0 0]
% A = A +A'
% error=R.ConnectF([2;3;4;6;7],[0,0,0,0,0],[0 0;0 1500;700 3000;1800 1500;2000 1000],[3*pi/2;0;pi/2;pi;pi])
% R.DefineNetwork('manual',A);
% [X Y] =R.GetPositionF
% R.RDV_Static(350,1.8,1)

%% 5 robots reels
% 
R = KheperaFleet(3,Ip)
% A = [0 0 0 0 1;0 0 0 1 1;0 0 0 0 1;1 0 1 0 0;0 0 0 0 0]
% A = A +A'
A = [0 1 0;1 0 1;0 1 0]

error=R.ConnectF([4;5;7],[0,0,0],[0 1500;700 3000;1800 1500],[0;pi/2;pi])
R.DefineNetwork('manual',A);
[X Y] =R.GetPositionF
% R.RDV_Static(410,1.8,1)
% 
% R.FleetFormation(3,'circle',700,1)
% R.FleetFormation(3,'line',[2 1000],1)
% 
% % R.StopMotors
% % R.SetVelocityF(80*[1;1.5;2;1.2;1.1],zeros(5,1))
% % 
% % R.Flocking(80*[1;1.5;1.2;1.2;0.8],1.5);
R.SetVelocityF(zeros(3,1),zeros(3,1))


