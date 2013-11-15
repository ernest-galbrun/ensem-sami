function Deplacement( k3,t )
c=tcpip('193.49.136.247',502); %Etablissement de la connection avec le superviseur 
fopen(c);
nb_robots = numel(t(:,1));



for l= 1 : nb_robots                     %boucle d'initialisation des variables et des robots.
    longueur_dir(l)=numel(t{l,4}(:,1)); %précise le nombre de déplcaments élémentaires
    arret(l)=false; % fin de la réalisation d'une mission -> dernier déplacement élémentaire du vecteur ci-dessus
    dernier(l)=0;  % enregistrer la position courante qui est le dernier lecteur rencontré 
    StartFollowLine(t{l,1},t{l,2},t{l,3});     %Démarage de tout les robots en suivi de ligne tout droit
    etape(l)=1; % Au début tout les robot sont à l'étape 1.
end

% la variable 'a' est utilisé pour savoir si tout les déplacements
% élémentaires de de tout les AGVs sont réalisés
a=true;    %Initialisation de a, qui sera la condition de sortie
while (a)
    a=false;
    for j= 1: nb_robots     %Boucle qui se répètera pour chacun des robots successivement
        X=appelpatch(t{j,1},c);     % X est un tableau contenant ce que chaque lecteur détecte
        r=Recherche(k3,j,X);    % cherche la position du patch du robot j. Renvoit 0 si le patch n'est pas devant un lecteur.
        %Vérification si le prochain noeud est avec conflit ou pas, si oui,
        %vérifier si la condition renseignée à l'exécution (par rapport au
        %lecteur de sortie de l'AGV prioritaire s'il détecte celcui-ci
        %(page29-30) si oui, alors autorisation de passage
        if(arret(j)==false) 
            t{j,4}(etape(j),2)=Auto(X,t{j,4}(etape(j),2)); % modifie l'autorisation d'un robot en fonction de la position des autres.
        end              
         
        %ce bloc X permet d'exécuter le déplacement élémentaire en question
        if(r~=0 && arret(j)==false && r~=dernier(j))    %Condition :robot j arrivé au lecteur suivant
            StopFollowLine(t{j,1});  % arrivé au lecteur, on arréte le robot et vérifie sa priorité dans la suite.   
            
            if(t{j,4}(etape(j),2)==0)   % cette valeur de la matrice t contient l'autorisation pour ce robot.
                dernier(j)=r;           % enregistre le numéro du dernier lecteur détecté (sécurité pour ne pas relancer le if (ligne 28) plusieur fois).
                t{j,1}.Cross(t{j,4}(etape(j),1),t{j,2},t{j,3}); % on lance le Cross pour ce robot avec ces valeur de direction, d'agressivité et de vitesse.
                etape(j)=etape(j)+1;    % on passe un lecteur donc on avance d'une étape. 
            end
        end
        % fin du bloc X
        
        %ici on vérifie pour le robot considéré s'il a fini sa mission, si
        %oui alors sa variable "arret" passe à true (alors qu'elle est
        %initialisée à false)
        if(etape(j)>=longueur_dir(j)+1)
            t{j,1}.StopFollowLine;
            arret(j)=true;  % Le robot j a fini son parcours.
        end
                
        
    end
    
    %ici on vérifie si tout les robots ont réalisés leur mission pour
    %-> pour sortir de la boucle infinie while
    for k=1: nb_robots
        a=a||etape(k)<=longueur_dir(k);     % a=false ssi tout les robots ont fini
    end
    
end

end


function [priorite] = Auto(X,priorite)
if priorite ~= 0              % Pour éviter d'appeler X(0), qui existe pas.
    
    if X(priorite)~=0      % test du passage d'un robot au lecteur p(i_robot).
        priorite=0;        % autorisation de passer en modifiant le vecteur p.
    end
end

end

