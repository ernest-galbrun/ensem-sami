function [P,T] = CompareConflit(k3,S1,T )

% 3 robots en conflit avec priorité double
% V1=[7 2;6 3;6 5;5 6]
% V2=[6 1;6 3;6 5;7 6]
% V3=[5 2;6 1]
% S1={V1 V2 V3}
% T{1,4}=V1;
% T{2,4}=V2;
% T{3,4}=V3;




% 3 robots en conflit
% V1=[7 2;6 3;6 5;7 6]
% V2=[6 7;5 6]
% V3=[6 1;5 2]
% S1={V1 V2 V3}
% T{1,4}=V1;
% T{2,4}=V2;
% T{3,4}=V3;

%2 robots en conflit
% V1=[7 2;6 3;6 5;7 6]
% V2=[6 7;5 6]
% S1={V1 V2}
% T{1,4}=V1;
% T{2,4}=V2;

%1 robots
% V1=[7 2;6 3;6 5;7 6]
% S1={V1}
% T{1,4}=V1;



Va=zeros(length (Noeuds(k3)),length(S1)); %Va n° des noeux sur les ligne et
%numéro des patch robot sur les colone.Ex Va(2,1)=1 si le robot 1
%passe par le neux deux
P=0;

for i1=1:length(S1)
    for j1=1:length(S1{:,i1}) %on rempli la matrice Va
        x=S1{:,i1};
        for k1=1:length(Noeuds(k3))
            if (AppelNoeud(k3,[x(j1,1) x(j1,2)])==k1)
                Va(k1,i1)=1;
            end
        end
    end
end

%Y a t il conflit?
if length(S1)>=2               %si il y a plus d'un robot
    for i2=1:length(Noeuds(k3))  %Crée tableau f[...] de dimension le nb de noeud
        f{1,i2}=0;
    end
    for i3=1:length(Noeuds(k3))     %Complete f avec la somme des lignes de Va
        for j3=1:length (Va)
            f{1,i3}=f{1,i3}+Va(i3,j3);
        end
    end
    
    conflit=0;
    for i4=1:length(Noeuds(k3))    %detecte si il y a des conflits ou pas
        if(f{1,i4}>=2)
            conflit=1;
        end
    end
else                  %Si il y a moin de deux robot
    conflit=0;
   
end
if(conflit==0)    %Si pas de conflit
    disp('Aucun conflit détecté'); disp(' ');
    for i5=1:length(S1)
        u1=T{i5,4}(:,1);
        u2=zeros(numel (u1),1);
        u3=zeros(numel (u1),1);
        T{i5,4}=[u1,u2,u3];
    end
else              %Si il y a conflit
    disp('un ou plusieurs conflits détectés'); disp(' ');
    
    %Priorité des robots
    for i6=1:length(S1)
        P(i6)=input(['Priorité du robot n°', num2str(i6),' (1,2,....)']);
    end
    P=P';
    for i7=length(P):-1:1%% On cherche le robot qui est le moins prioritaire.
        j7=1;
        while(P(j7)~=i7)
            j7=j7+1;
        end
        W=S1{:,j7};
        p=zeros(length(W),1);
        q=zeros(length(W),1);
        C=0;% Compteur pour savoir si il n'y a aucune priorité à prendre en compte
        VaY=Va(:,j7); %% Une fois trouvé le robot on regarde si il passe par des croisements.
        for k1=1:length(VaY)
            
            if VaY(k1)==1 %% Si oui alors on regarde si d'autres robots y passe aussi
                VaX=Va(k1,:);
                a=0;         
                for z=1:length(VaX)                    
                    if z~=j7&&VaX(z)==1 &&  P(z)>a %Si d'autres robots passent par le même croisement, on va chercher les coordonnées d'entrées
                        % du robot le moins prioritaire pour remplir la matrice p
                        % Ainsi que les coordonnées qui
                        % permettrons de faire redémarrer le
                        % robot
                        C=1;
                        no=1;
                        
                        if (AppelNoeud(k3,[W(no,1) W(no,2)])==k1)
                            p(no)=z;
                        end
                        
                        while(AppelNoeud(k3,[W(no,1) W(no,2)])~=k1)
                            no=no+1;
                            if (AppelNoeud(k3,[W(no,1) W(no,2)])==k1)
                                p(no)=z;
                            end
                            
                        end % Fin de p début de q
                        Z=S1{:,z};
                        n=2;
                        while(AppelNoeud(k3,[Z(n-1,1) Z(n-1,2)])~=k1)
                            n=n+1;
                        end
                        q(no)=AppelCapteur(k3,[Z(n,1) Z(n,2)]);%si il y a eu des priorité à prendre en compte. On renvoi p et q modifiés
                        u1=T{j7,4}(:,1);
                        u2=zeros(numel (u1),1);
                        u3=zeros(numel (u1),1);
                        for b=1:numel(p)
                            u2(b,1)=p(b,1);
                            u3(b,1)=q(b,1);
                        end
                        T{j7,4}=[u1,u2,u3];
                        a=P(z);
                        
                        
                    end
                    
                end
                
                
                
            end
            
            Va(k1,j7)=0;
            
        end
        if C==0 %si il n'y a aucune priorité à prendre en compte. On renvoi p et q null
            u1=T{j7,4}(:,1);
            u2=zeros(numel (u1),1);
            u3=zeros(numel (u1),1);
            T{j7,4}=[u1,u2,u3];
        end
    end
    
    
end