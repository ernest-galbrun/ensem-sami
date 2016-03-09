function [  ] = WritePatch(slave,val)
%Sert à écrire une valeur sur un patch
c=tcpip('193.49.136.247',502);
fopen(c);% on ouvre la connexion

WriteRegister(c,[18 185],[0 0]); %initialiser à 0 pour préparer l'opération

WriteRegister(c,[18 186],WriteCommand(35,slave,val));%écrire la commande sur le contrôleur

WriteRegister(c,[18 185],[0 101]);% effectuer la commande

end

