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
tVol=30; % Temps de vol en secondes
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

%% initaialisation du système
initCortex(); % initialisation de Cortex
configDrone(port,altMax,eulerMax,yawMax); % Configuration du drone

%% gestion du vol
decollage(port); % Decollage du drone

tic
errors = [];
while(toc<tVol)
    % Enregistrement du temps
    saveTps(compteur,:) = toc;
    % Mesures cortex et calcul du point désigné par la baguette
    [dataDrone, dataWand] = getSceneData();    
%     hoverPoint = [0 0 zRef];
    hoverPoint = getHoverPoint(dataWand, zRef);
    % Traitement et envoi commande
    cmd = commandeVol(dataDrone,hoverPoint,port);
%     pause(0.05); % pause à 0.1 -> instable
    % Sauvegarde des logs et incrémentationdu compteur
    saveDrone(compteur,:) = dataDrone;
    saveHover(compteur,:) = hoverPoint;
    saveCmd(compteur,:) = cmd;
    compteur = compteur + 1;
end;

atterissage(port); % Atterrissage du drone
fclose(port); % fermeture du port UDP

%% Affichage du vol
plotVol(saveTps,saveDrone,saveHover,saveCmd);

