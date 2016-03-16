 function [ D, W ] = getSceneData()
%getDroneData r�cup�re les donn�es drone et baguette de cortex     
%   r�cup�re les 3 positions (x,y,z) et les 3 angles(yaw,pitch,roll) du drone, le vecteur directeur et un point de la baguette

% d�claration des pointeurs qui vont recevoir les donn�es
    % donn�es drone
    xD = libpointer('doublePtr',0);
    yD = libpointer('doublePtr',0);
    zD = libpointer('doublePtr',0);
    yawD = libpointer('doublePtr',0);
    pitchD = libpointer('doublePtr',0);
    rollD = libpointer('doublePtr',0);
    % donn�es baguette
    xvW = libpointer('doublePtr',0);
    yvW = libpointer('doublePtr',0);
    zvW = libpointer('doublePtr',0);
    xpW = libpointer('doublePtr',0);
    ypW = libpointer('doublePtr',0);
    zpW = libpointer('doublePtr',0);
% ouverture de cortex
calllib('khepera3clib', 'OpenCortex');
% r�cup�ration des donn�es
calllib('khepera3clib', 'GetDronePosition',xD,yD,zD,yawD,pitchD,rollD);
calllib('khepera3clib', 'GetWandDirection',xvW,yvW,zvW,xpW,ypW,zpW);
% stockage
D = [xD.value yD.value zD.value yawD.value pitchD.value rollD.value];
W = [xvW.value yvW.value zvW.value xpW.value ypW.value zpW.value];
end

