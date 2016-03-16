close all
time=-200:0.001:200;
%DEMI_GRAND_AXE=50;
Xpos=[0 0];
DEMI_GRAND_AXE=500;
%           DEMI_PETIT_AXE=250;
%           xRef=Xpos(1) - DEMI_GRAND_AXE + DEMI_GRAND_AXE*cos(time;
%           yRef=Xpos(2) + DEMI_PETIT_AXE*sin(time;
       
% xRef=Xpos(1)*ones(1,length(time)) + DEMI_GRAND_AXE*sin(time)./(ones(1,length(time))+cos(time).^2);
%           yRef=Xpos(2)*ones(1,length(time)) + DEMI_GRAND_AXE*sin(2*time).*cos(time)./(ones(1,length(time))+cos(time).^2);
%          figure();
%           plot(xRef,yRef)
%          
         %mod
         t=-5:0.2:5;
x=Xpos(1)*ones(1,length(t))+(2*t)./(1+t.^4)*400;
y=Xpos(2)*ones(1,length(t))+(2*t.^3)./(1+t.^4)*400;
x=-x;
y=-y;
figure();
plot(x,y,'+')
title('lemniscate de Bernouilli')
xlabel('x')
ylabel('y')
grid on
tVol=7;
time=0:00.1:tVol;
if(time<tVol/2)
              xRef=Xpos(1) + 400*(2*time)./(1+time.^4);
              yRef=Xpos(2) + 400*(2*time.^3)./(1+time.^4);
          else
              time=-(tVol/2-time);
              xRef=Xpos(1) + 400*(2*time)./(1+time.^4);
              yRef=Xpos(2) + 400*(2*time.^3)./(1+time.^4);
          end
              xRef=-xRef;
              yRef=-yRef;


