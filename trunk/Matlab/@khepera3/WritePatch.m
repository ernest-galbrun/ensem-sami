function [  ] = WritePatch(k3,slave,val)
%Sert à écrire une valeur sur un patch
c=tcpip('193.49.136.247',502);
fopen(c);% on ouvre la connexion

WriteRegister(k3,c,[18 185],[0 0]); %initialiser à 0 pour préparer l'opération

WriteRegister(k3,c,[18 186],WriteCommand(k3,35,slave,val));%écrire la commande sur le contrôleur

WriteRegister(k3,c,[18 185],[0 101]);% effectuer la commande

end

