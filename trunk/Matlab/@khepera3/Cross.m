function Cross( k3,id, dr, agr, vel ) % dr= direction du robot avec 0=tout droit; 1=à droite; 2=à gauche.
global B;
global tourn; % Variables conservées pour chaque utilisation du programme.
global arret;

if dr==0 
    % on ne fait rien.
else
    V=k3.GetIRProximity; % Vecteur infrarouge
if (tourn(id)==false && V(10)>3800 && V(11)>3800) % Test d'arrivée a une intersection
    % Prépare le robot à tourner:
    k3.StopFollowLine;                        
    A=k3.GetOrientation;
    B(id)=A;
    calllib('khepera3clib', 'StartMotors',k3.id);
    tourn(id)=true;
end

if (tourn(id) && arret(id)==false && (V(3)>300 || V(4)>300 || V(5)>300 || V(6)>300))
    arret(id)=true;
    calllib('khepera3clib', 'StopMotors',k3.id);
end
if(tourn(id) && arret(id) && V(3)<=300 && V(4)<=300 && V(5)<=300 && V(6)<=300)
    calllib('khepera3clib', 'StartMotors',k3.id);
    arret(id)=false;
end

A=k3.GetOrientation; % Orientation des roues.
if dr==1
    if (tourn(id) && A>B(id)-1.57)      % Test actif quand le robot tourne
        calllib('khepera3clib', 'SetSpeed',k3.id,50,-0.8);
    end
    
    if (tourn(id) && A<=B(id)-1.57)         % Test de fin de virage
         % Remet le robot en mode normal:
        calllib('khepera3clib', 'StopMotors',k3.id);
        k3.StartFollowLine(agr,vel);
        tourn(id)=false;
    end
else % Idem mais dans l'autre sens.
     if (tourn(id) && A<B(id)+1.57)
        calllib('khepera3clib', 'SetSpeed',k3.id,50,0.8);
    end
    
    if (tourn(id) && A>=B(id)+1.57)
        calllib('khepera3clib', 'StopMotors',k3.id);
        k3.StartFollowLine(agr,vel);
        tourn(id)=false;
    end
        
end


end

end

