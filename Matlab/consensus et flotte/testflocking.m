% Test flocking

clear all
close all
clc 

R = KheperaFleet(4);
R.ConnectF([10,11,12,13],[1,1,1,1],-500+1000*rand(4,2),rand(4,1))
R.DefineNetwork('manual',[0,1,0,0;1,0,0,1;0,0,0,1;0,1,1,0])

R.SetVelocityF(100*[0.1;0.2;0.9;1.2],[0.08;0.05;0.04;0.1]);
R.Flocking(100*[0.1;0.2;0.9;1.2]);