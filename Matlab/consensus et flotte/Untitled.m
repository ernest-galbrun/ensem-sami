clear all
close all
clc

R = KheperaFleet(3);
R.ConnectF([2,7,5],[0,0,0,0],[0 0;0 0;0 0;0 0],[0;0;0;0])
R.DefineNetwork('manual',[0,1,0;1,0,1;0,1,0])


 R.RDV_Static(150,50)

R.SetVelocityF(zeros(3,1),zeros(3,1));