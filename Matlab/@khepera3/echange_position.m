function echange_position(k3,patch1,patch2,prio,t)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
c=tcpip('193.49.136.247',502);
fopen(c);
for i=1:length(t(:,1))
    V(i)=i;
end

while(sum(V)~=0)
    for j=1:length(t(:,1))
        X=appelpatch(t{1,1},c);
        r=Recherche(t{1,1},j,X);
        if(r~=0)
            StopFollowLine(t{j,1});
            V(j)=0;
        end
    end
end

position1=[0 0];
position2=[0 0];
PATCH=appelpatch(k3,c);
pivot=[0 0];
for i=1:length(PATCH)
    if(PATCH(i)==patch1)
        position1=positioncapteur(k3,i);
    end
    if(PATCH(i)==patch2)
        position2=positioncapteur(k3,i);
    end
    nb_robots=length(t);
end
%Si un problème est détecté, on arrete tous les robots sur les capteurs.
for j= 1: nb_robots
    V(j)=j;
end



numero1=prio(patch1);%GetPriority(patch1)
numero2=prio(patch2);%GetPriority(patch2)

positionprio=zeros(1,2);
positionnonprio=zeros(1,2);

%On renomme prio le patch prioritaire et nonprio le non prioritaire,
%pour ne pas avoir a ecrire les programmes 2 fois en fonction de la
%priorité

if (numero1<numero2)
    patchnonprio=patch2;
    patchprio=patch1;
    positionprio(1)=position1(1);
    positionprio(2)=position1(2);
    positionnonprio(1)=position2(1);
    positionnonprio(2)=position2(2);
end
if (numero2<numero1)
    patchnonprio=numero1;
    patchprio=numero2;
    positionprio(1)=position2(1);
    positionprio(2)=position2(2);
    positionnonprio(1)=position1(1);
    positionnonprio(2)=position1(2);
end
e=0;
f=0;
%On cherche une position pivot qui permettra de faire l'echange en 3
%temps

k=0; %k "arrêtera" la recherche après avoir
%trouvé une position satisfaisante
for i=positionnonprio(1)-2 : positionnonprio(1)+2
    for j=positionnonprio(2)-2 : positionnonprio(2)+2
        abscisse=abs(positionnonprio(1)-i);
        ordonnee=abs(positionnonprio(2)-j);
        b=AppelCapteur(k3,[i j]);
        if (k==0 && b~=0 && PATCH(b)==0 && ((abscisse==1 && ordonnee==1)||(abscisse==0 && ordonnee==2)||(abscisse==2 && ordonnee==0)))
            %détail des conditions :
            %k==0 -> Si on a toujours pas trouvé de position
            %b~=0 -> Si la position {i,j} est bien un capteur
            %appelpatch -> Si le capteur n'a pas de robot sur lui
            % abscisse et ordonnée -> Si on se déplace bien de 2 cases
            
            k=1;% pour éviter d'en chercher un autre
            e=i;
            f=j;
            pivot=[e f];
        end
    end
end

%Puis on déplace physiquement les robots

%les moves représentent les vecteurs de déplacements élémentaires
move(1,1:2)=[e-positionnonprio(1) f-positionnonprio(2)];
move(2,1:2)=[e-positionnonprio(1) f-positionnonprio(2)];
move(3,1:2)=[positionnonprio(1)-positionprio(1) positionnonprio(2)-positionprio(2)];
move(4,1:2)=[positionprio(1)-e positionprio(2)-f];
% Les points sont les arrivées des déplacements élémentaires
point(1,1:2)=pivot;
point(2,1:2)=pivot;
point(3,1:2)=positionnonprio;
point(4,1:2)=positionprio;
% Le patch i correspond au robot qui effectue de déplacement élément. i
patch(1)=patchnonprio;
patch(2)=patchnonprio;
patch(3)=patchprio;
patch(4)=patchnonprio;
%On cherche la position des centres adjacents aux
centre2=positioncentre(AppelNoeud(k3,positionprio));
centre1=positioncentre(AppelNoeud(k3,positionnonprio));

%On sépare le cas où les centres sont identiques ou non ( on travaille
%avec 1 ou 2 noeuds)
if (centre1==centre2)
    %dans le 1er "if", on regarde la forme de la flèche entre le
    %point de départ et d'arrivée
    %dans le 2eme "if", on regarde la position de l'arrivée par rapport
    %au centre
    for i=1:4 % Pour chacun des 3 mouvements...
        if i==2
            StartFollowLine(t{patch(i),1},1,5000);
            pause(1);
            Cross(t{patch(i),1},3,1,5000);%demi tour du non prio
            pause(3.4);
            StopFollowLine(t{patch(i),1});
            
        else if (move(i,1)>0 && move(i,2)>0)%flèche pointe vers haut droite
                if (centre1(1)==point(i,1))
                    Cross(t{patch(i),1},2,1,5000);
                end
                if (centre1(2)==point(i,2))
                    Cross(t{patch(i),1},1,1,5000);
                end
            end
            if (move(i,1)>0 && move(i,2)<0)%flèche pointe vers bas droite
                if (centre1(1)==point(i,1))
                    Cross(t{patch(i),1},1,1,5000);
                end
                if (centre1(2)==point(i,2))
                    Cross(t{patch(i),1},2,1,5000);
                end
            end
            if (move(i,1)<0 && move(i,2)>0)%flèche pointe vers haut gauche
                if (centre1(1)==point(i,1))
                    Cross(t{patch(i),1},1,1,5000);
                end
                if (centre1(2)==point(i,2))
                    Cross(t{patch(i),1},2,1,5000);
                end
            end
            if (move(i,1)<0 && move(i,2)<0)%flèche pointe vers bas gauche
                if (centre1(1)==point(i,1))
                    Cross(t{patch(i),1},2,1,5000);
                end
                if (centre1(2)==point(i,2))
                    Cross(t{patch(i),1},1,1,5000);
                end
            end
            if (move(i,1)==0 || move(i,2)==0)%flèche a 1 seule composante
                Cross(t{patch(i),1},0,1,5000);
            end
        
        PATCH=appelpatch(k3,c);    
        r=Recherche(k3,patch(i),PATCH);
        while r~=AppelCapteur(k3,point(i,1:2))
            PATCH=appelpatch(k3,c);
            r=Recherche(k3,patch(i),PATCH);
        end
        end
        StopFollowLine(t{patch(i),1});
        
    end
end
if (centre1~=centre2)% <=> Si les robots sont en ligne
    % On fait reculer le robot non prioritaire sur le pivot
    i=1;% On est en fait à la 1ere étape de move
    Cross(t{patch(i),1},3,1,5000);
    if (move(i,1)>0 && move(i,2)>0)%flèche pointe vers haut droite
        if (centre1(1)==point(i,1))
            Cross(t{patch(i),1},2,1,5000);% tourne à gauche
        end
        if (centre1(2)==point(i,2))
            Cross(t{patch(i),1},1,1,5000);% tourne à droite
        end
    end
    if (move(i,1)>0 && move(i,2)<0)%flèche pointe vers bas droite
        if (centre1(1)==point(i,1))
            Cross(t{patch(i),1},1,1,5000);% tourne à droite
        end
        if (centre1(2)==point(i,2))
            Cross(t{patch(i),1},2,1,5000);% tourne à gauche
        end
    end
    if (move(i,1)<0 && move(i,2)>0)%flèche pointe vers haut gauche
        if (centre1(1)==point(i,1))
            Cross(t{patch(i),1},1,1,5000);% tourne à droite
        end
        if (centre1(2)==point(i,2))
            Cross(t{patch(i),1},2,1,5000);% tourne à gauche
        end
    end
    if (move(i,1)>0 && move(i,2)<0)%flèche pointe vers bas gauche
        if (centre1(1)==point(i,1))
            Cross(t{patch(i),1},2,1,5000);% tourne à gauche
        end
        if (centre1(2)==point(i,2))
            Cross(t{patch(i),1},1,1,5000);% tourne à droite
        end
    end
    if (move(i,1)==0 || move(i,2)==0)%flèche pointe vers haut gauche
        Cross(t{patch(i),1},0,1,5000);% va tout droit
    end
    
    Cross(t{patch(i),1},3,1,5000);
    PATCH=appelpatch(k3,c);     % X est un tableau contenant ce que chaque lecteur détecte
    r=Recherche(k3,patch(i),PATCH);
    while r~=AppelCapteur(k3,point(i,1:2))
        PATCH=appelpatch(k3,c);
        r=Recherche(k3,patch(i),PATCH);
    end
    StopFollowLine(t{patch(i),1});
    %puis on fait avancer le robot prioritaire
    i=2;% 2eme etape...
    Cross(t{patch(i),1},0,1,5000);
    PATCH=appelpatch(k3,c);     % X est un tableau contenant ce que chaque lecteur détecte
    r=Recherche(k3,patch(i),PATCH);
    while r~=AppelCapteur(k3,point(i,1:2))
        PATCH=appelpatch(k3,c);
        r=Recherche(k3,patch(i),PATCH);
    end
    StopFollowLine(t{patch(i),1});
    
    %Puis on revient au cas où les centres sont identiques...
    echange_position(a,patch1,patch2, position1, position2, prio,t);
end
end
