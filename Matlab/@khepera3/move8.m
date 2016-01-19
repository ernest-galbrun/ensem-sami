%fonction determinant le chemin � prendre en fonction de l'orientation O du robot, sa position de d�part D et la destination (position d'arriv�e) A
%renvoie t le vecteur des directions du robot (et �ventuellement D pour la r�cursivit�)
%D et A rep�r�s par leur coordonn�es dans la config choisie D=[xD yD] A=[xA yA] (dans le prog xD s'appelle D(1), yD D(2), xA A(1); yA A(2))

%PRISE EN COMPTE DE L'ORIENTATION PAS COMPLETEMENT IMPLEMENTEE POUR L'INSTANT 

function [t,D,O,V] = move8(O,D,A)
t=[];%initialisation de t, vide par d�faut
V=D;
if(A==D)%cas ou on est arriv� pour clore la r�cursion : on ne fait rien (sinon : r�cursion)
else

if (D(1)~=A(1))%                      dx et dy unitaires donnent respectivement la direction de l'arriv�e selon x et y. Dans la config choisie pour tout d�placement 
    dx=((A(1)-D(1))/abs(A(1)-D(1)));   % la somme des variations absolues selon x et y est �gale � 2. En clair si on va tout droit :x=x +- 2dx OU y=y +- 2dy
else dx=0;                             %Si on tourne x=x +- dx ET y=y +- dy Se voit clairement sur un sch�ma
end
if (D(2)~=A(2))
    dy=((A(2)-D(2))/abs(A(2)-D(2)));
else dy=0;
end


if (rem(D(1),2)==0)
    if(dy*imag(O)<0)
        t=[t;3;0];disp('demi-tour');O=-O;
    end
else
    if(dx*real(O)<0)
        t=[t;3;0];disp('demi-tour');O=-O;
    end
end


if (D(2)==A(2))                   %cas ou D et A sont � m�me ordonn�e (dy==0) 
    if (rem(A(2),2)==0)           % si on peut se d�placer directement selon x (c-a-d y est pair) on va directement � A, sinon on tourne, avance selon x, retourne.
        for i=1:(abs(A(1)-D(1))/2)
            t=[t;0];%disp('tout droit');
            D(1)=D(1)+2*dx;V=[V;D];%disp('position :');disp(D);
        end
        
    else
        if (rem(D(2)+dx,4)==0) % d�termine ou est l'int�rieur du noeud (si yD + dx est divisible par 4 l'int�rieur est en (xD +dx,yD-dx) sinon (xD +dx,yD+dx))
            [u D O W]=move8(O,D,[D(1)+dx,D(2)-dx]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,[A(1)-dx,D(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
        else
            [u D O W]=move8(O,D,D+dx);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,[A(1)-dx,D(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
        end
    end
    
elseif(D(1)==A(1))                   %cas ou D et A sont � m�me abscisse (dx==0)

    if (rem(A(1),2)==0)           % si on peut se d�placer directement selon y (c-a-d x est pair) on va directement � A, sinon on tourne, avance selon x, retourne.
        for i=1:(abs(D(2)-A(2))/2);
                t=[t;0];%disp('tout droit');
                D(2)=D(2)+2*dy;V=[V;D];%disp('position :');disp(D);
        end
        
    else
        if (rem(D(1)+dy,4)==0)
            [u D O W]=move8(O,D,[D(1)-dy,D(2)+dy]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,[D(1),A(2)-dy]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
        else
            [u D O W]=move8(O,D,D+dy);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,[D(1),A(2)-dy]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
        end
    end
    
else                      %abscisse et ordonn�es de d�part et arriv�es diff�rentes, il faut se ramener � un des deux cas pr�c�dents
    if (rem(D(1),2)==0)
        if (rem(A(1),2)==0)
            if (rem(A(2)+dy,4)==0)
                [u D O W]=move8(O,D,[D(1),A(2)-2*dy]);t=[t;u];V=[V;W(2:numel(W)/2,:)];
                [t D O V]=movedir(O,D,A,V,dx,dy,t);
                [u D O W]=move8(O,D,[A(1)-dx,D(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];
                [t D O V]=movedir(O,D,A,V,dx,dy,t);
            else
                [u D O W]=move8(O,D,[D(1),A(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
            end
            
        else
            [u D O W]=move8(O,D,[D(1),A(2)-dy]);t=[t;u];V=[V;W(2:numel(W)/2,:)];
            [t D O V]=movedir(O,D,A,V,dx,dy,t);
            [u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
        end
    else
        if (rem(A(2),2)==0)
            if (rem(A(1)+dx,4)==0)
                [u D O W]=move8(O,D,[A(1)-2*dx,D(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];
                [t D O V]=movedir(O,D,A,V,dx,dy,t);
                [u D O W]=move8(O,D,[D(1),A(2)-dy]);t=[t;u];V=[V;W(2:numel(W)/2,:)];
                [t D O V]=movedir(O,D,A,V,dx,dy,t);
            else
                [u D O W]=move8(O,D,[A(1),D(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];[u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
            end
        else
            [u D O W]=move8(O,D,[A(1)-dx,D(2)]);t=[t;u];V=[V;W(2:numel(W)/2,:)];
            [t D O V]=movedir(O,D,A,V,dx,dy,t);
            [u D O W]=move8(O,D,A);t=[t;u];V=[V;W(2:numel(W)/2,:)];
        end
end
end
end
end
