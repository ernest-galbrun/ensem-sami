function [  ] = WritePatch(slave,val)
%Sert � �crire une valeur sur un patch
c=tcpip('193.49.136.247',502);
fopen(c);% on ouvre la connexion

WriteRegister(c,[18 185],[0 0]); %initialiser � 0 pour pr�parer l'op�ration

WriteRegister(c,[18 186],WriteCommand(35,slave,val));%�crire la commande sur le contr�leur

WriteRegister(c,[18 185],[0 101]);% effectuer la commande

end

