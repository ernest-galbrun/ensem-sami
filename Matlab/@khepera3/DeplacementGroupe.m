function [  ] = DeplacementGroupe( k3,t )
c=tcpip('193.49.136.247',502);%Etablissement de la connection
fopen(c);
nb_robots = numel(t(:,1));



for l= 1 : nb_robots                     %boucle d'initialisation des variables et des robots.
    longueur_dir(l)=numel(t{l,4}(:,1));
    arret(l)=false;
    dernier(l)=0;   
    StartFollowLine(t{l,1},t{l,2},t{l,3});     %Démarage de tout les robots
    
end

for j=1:nb_robots
    etape(j)=1;
end
a=true;    %Initialisation de a, qui sera la condition de sortie
while (a)
    a=false;
    for j= 1: nb_robots %Boucle qui se répètera pour chacun des robots successivement
        X=appelpatch(t{j,1},c); % X est un tableau contenant ce que chaque lecteur détecte
        r=Recherche(k3,j,X); % cherche la position du patch
       
        if(r~=0 && arret(j)==false && r~=dernier(j))%Condition :robot j arrivé au lecteur suivant
            dernier(j)=r;%enregistre le numéro du dernier lecteur détecté
            StopFollowLine(t{j,1});
            disp(t{j,4}(etape(j),1));
            t{j,1}.Cross(t{j,4}(etape(j),1),t{j,2},t{j,3});
             disp(42)
            etape(j)=etape(j)+1;
            
        end
        
        
        
        
        if(etape(j)==longueur_dir(j)+1)
            t{j,1}.StopFollowLine;
            arret(j)=true;
        end
        
    end
    
    
    for k=1: nb_robots
        a=a||etape(k)<=longueur_dir(k); %a=false ssi tout les robots ont fini
    end

end

