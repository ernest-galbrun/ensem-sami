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

%Homogénéité mm -> m
Xpos(1:3)=Xpos(1:3)/1000;
Xpos(5:6)=Xpos(5:6)/1000; 
Xref=Xref/1000;

% K(1) et K(2) < 0, orientation salle + effet commande
Kcor=[-1/4 -1/4 1 -1.5]/2;

%Calcul des commandes à appliquer
commandeOut(1)=Kcor(1)*(Xref(2)-Xpos(2));
commandeOut(2)=Kcor(2)*(Xref(1)-Xpos(1));
commandeOut(3)=Kcor(3)*(Xref(3)-Xpos(3));
commandeOut(4)=Kcor(4)*(-Xpos(4));

%Saturation des commandes
commandeOut=saturationCommande(commandeOut,-1,1);

%Priorite des commandes
% Ordre Z tout le temps, Yaw en priorité, puis roll ou pitch
if abs(commandeOut(4)/Kcor(4))>0.2
    commandeOut(1)=0;
    commandeOut(2)=0;
    display('Yaw');
else
    commandeOut(4)=0;
    if abs(commandeOut(1))>abs(commandeOut(2))
        commandeOut(2)=0;
        display('Roll');
    else
        commandeOut(1)=0;
        display('Pitch');
    end;
end;

%Zone morte
if sqrt((Xref(1)-Xpos(1))^2+(Xref(2)-Xpos(2))^2)<=0.15
    flag=0;
else
    flag=1;
end;
disp(flag);

%Conversion et envoie des commandes
fwrite(port,sprintf('AT*PCMD=%d,%d,%d,%d,%d,%d\r',sequenceNumber,flag,typecast(single(commandeOut(1)),'int32'),typecast(single(commandeOut(2)),'int32'),typecast(single(commandeOut(3)),'int32'),typecast(single(commandeOut(4)),'int32')));
sequenceNumber=sequenceNumber+1;
end