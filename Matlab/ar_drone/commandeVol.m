function [commandeOut]=commandeVol(Xpos,Xref,port)

%commandeOut(1) : commande roll
%commandeOut(2) : commande pitch
%commandeOut(3) : commande vitesse verticale
%commandeOut(4) : commande vitesse yaw

%Xpos(1) : x
%Xpos(2) : y
%Xpos(3) : z
%Xpos(4) : yaw
%Xpos(5) : vitesse forward
%Xpos(6) : vitesse laterale

%Xref(1) : xref
%Xref(2) : yref
%Xref(3) : zref

%Gestion du sequence number
global sequenceNumber;
global errors;
global errors_x;
global errors_y;

%Homogénéité mm -> m
Xpos(1:3)=Xpos(1:3)/1000;
Xpos(5:6)=Xpos(5:6)/1000; 
Xref=Xref/1000;

%Gain
Kpitch= -0.4;
Kroll = -0.4;
Kd = -100;
Kyaw= -1.;
d = 2.;

%Calcul des commandes à appliquer

%Commande ROLL
commandeOut(1)=0;

%Commande PITCH
Ex=Xref(1)-Xpos(1);
Ey=Xref(2)-Xpos(2);
e=sqrt((Ex)^2+(Ey)^2);
yawCom=atan2(Ey,Ex);
%if yawCom<0
%    yawCom=yawCom+2*pi;
%end;
yaw = Xpos(4);
Etheta=yawCom-yaw;
if(Etheta>pi)
    Etheta = Etheta-2*pi;
elseif(Etheta<-pi)
    Etheta=Etheta+2*pi;
end
errors = [errors e];
errors_x = [errors_x Ex];
errors_y = [errors_y Ex];
commandeOut(1)= Kroll * e * sin(Etheta);
commandeOut(2)= Kpitch * e * cos(Etheta);

if length(errors) > 5
    dd = mean(diff(errors(end-5:end)));
    dd_x = mean(diff(errors_x(end-5:end)));
    dd_y = mean(diff(errors_y(end-5:end)));
    %Kd * dd * sin(Etheta);
    commandeOut(1) = commandeOut(1) + Kd * dd * sin(Etheta);
    commandeOut(2) = commandeOut(2) + Kd * dd * cos(Etheta);
    %commandeOut(1) = commandeOut(1) + Kd * dd_y * sin(Etheta)+ Kd * dd_x * cos(Etheta);
    %commandeOut(2) = commandeOut(2) + Kd * dd_x * sin(Etheta)+ Kd * dd_y * cos(Etheta);
end

% commandeOut(2)=0;
%Commande Z
commandeOut(3)=1.5*(Xref(3)-Xpos(3));

%Commande YAW
commandeOut(4)= 0 ;%Kyaw*(Etheta)*(1/(1+(d/e)^2));

%Saturation des commandes
commandeOut=saturationCommande(commandeOut,-1,1);

flag=1;
if(isnan(Xpos(3)) || Xpos(3)==0) %arrete de le drone si jamais il sort des caméras
    commandeOut(1)= 0;
    commandeOut(2)= 0;
    commandeOut(3)= -0.1;
    commandeOut(4)= 0;
   %commandeOut=zeros(4);
   %flag=0;
end
%Conversion et envoie des commandes
fwrite(port,sprintf('AT*PCMD=%d,%d,%d,%d,%d,%d\r',sequenceNumber,flag,typecast(single(commandeOut(1)),'int32'),typecast(single(commandeOut(2)),'int32'),typecast(single(commandeOut(3)),'int32'),typecast(single(commandeOut(4)),'int32')));
sequenceNumber=sequenceNumber+1;
end