clear all
close all
clc

%% Gestion des ports de communication
port = udp('192.168.1.1',5556);%Port envoie commande
fopen(port); 

%% Gestion des numéros de séquence
global sequenceNumber;
global errors;
sequenceNumber=0;

%% initialsation des variables et configuration
tVol=10; % Temps de vol en secondes
zRef=800; % Altitude du plan de vol (en mm)
altMax=1500; % Altitude max autorisée
eulerMax=0.2;% Angle max de roll et pitch
yawMax=6; % Vitesse de yaw max en rad/s
% vecteurs de données temporaires
dataDrone = zeros(1,6);
dataWand = zeros(1,6);
% sauvegarde des données de vol
compteur = 1;
saveTps = zeros(3000,1);
saveDrone = zeros(3000,6);
saveHover = zeros(3000,3);
saveCmd = zeros(3000,4);

%% Choix du mode de suivi de trajectoire 
mode=2; %(1=suivi de la baguette / 2=suivi d'une trajectoire de référence)
typeTrajectoire=1; %(0=point / 1=cercle / 2=ellipse /3 lemniscate de Bernouilli)

%% initaialisation du système
initCortex(); % initialisation de Cortex
configDrone(port,altMax,eulerMax,yawMax); % Configuration du drone

%% gestion du vol
decollage(port); % Decollage du drone
tic
if mode ==2      %Recupere la position du drone aprés le décollage
    [dataDroneInit,~] = getSceneData();
    timeInit=toc;
end

errors = [];
Stop=0;
while(toc<tVol && Stop==0)
    % Enregistrement du temps
    saveTps(compteur,:) = toc;
    % Mesures cortex et calcul du point désigné par la baguette
    [dataDrone, dataWand] = getSceneData();    
%     hoverPoint = [0 0 zRef];
    if mode==1
        hoverPoint = getHoverPoint(dataWand, zRef);
        % Traitement et envoi commande
        cmd = commandeVol(dataDrone,hoverPoint,port);
    elseif mode==2
        
        
         [trajectoirePoint,Stop] = getTrajectoirePoint( dataDroneInit,typeTrajectoire, toc,zRef,tVol);
         % Traitement et envoi commande
            cmd = commandeVol(dataDrone,trajectoirePoint,port);
            
%          %On lui laisse le temps de se stabiliser
%                 for i=sequenceNumber:sequenceNumber+100
%                     sequenceNumber=sequenceNumber+1;
%                     fwrite(port,sprintf('AT*COMWDG=%d\r',sequenceNumber)); 
%                 pause(0.05);
%                 end
    else
        disp('erreur mode')
        mode=1;
    end
%     pause(0.05); % pause à 0.1 -> instable
    % Sauvegarde des logs et incrémentationdu compteur
    saveDrone(compteur,:) = dataDrone;
    if(mode==1)
        saveHover(compteur,:) = hoverPoint;
    elseif (mode==2)
        saveHover(compteur,:) = trajectoirePoint;
    else
        disp('erreur mode')
    end
    saveCmd(compteur,:) = cmd;
    compteur = compteur + 1;
end;

atterissage(port); % Atterrissage du drone
fclose(port); % fermeture du port UDP

%% Affichage du vol
plotVol(saveTps,saveDrone,saveHover,saveCmd);

