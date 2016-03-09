function  count=carre(k3,dir,agr,vel) % fonction test de la fonction Cross qui faittourner un ou plusieurs robots sur un carré, toujours dans le même sens.
                                        % elle n'a plus d'intérêt depuis la finalisation et l'implémentation  de la fonction Cross sur les khepera. 
c=tcpip('193.49.136.247',502);
fopen(c);
fwrite(c,uint8([0 0 0 0  0 6 1 4 hex2dec('10') hex2dec('21') 0 1]),'uint8');
X=fread(c,11);
val=X(10);
val=0;
global B;
global tourn;
global arret;
arret(1)=false; %arret(2)=false;
tourn(1)=false; %tourn(2)=false; %test pour connaitre l'activité du robot; followline ou rotation
count=0;
on=true; 
% les variables globales sont utiles pour tester la fonction Crossarchive.

k3.StartFollowLine(agr,vel);
%k2.StartFollowLine(agr,vel);

while on
    count=count+1; %compteur du nombre de boucle du programme pour évaluer la rapidité de la fonction Cross
    fwrite(c,uint8([0 0 0 0  0 6 1 4 hex2dec('10') hex2dec('21') 0 1]),'uint8');
    X=fread(c,11);
    val=X(10);
    if val==125 %test de tous les patch(ici 1 seul patch pour fin du programme)
        if tourn
            calllib('khepera3clib', 'StopMotors',k3.id);
        else k3.StopFollowLine;
        end
        on=false; %condition de fin de programme: patch détecté.
    end
    
    Cross(k3,1,dir,agr, vel);
    %Cross(k2,2,dir,agr, vel);
    
     
    
end

return
end