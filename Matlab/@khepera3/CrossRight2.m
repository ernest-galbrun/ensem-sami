function CrossRight2(k3,agr,vel)
StartFollowLine(k3,agr,vel);
tourn=false;
A=k3.GetOrientation; % Orientation des roues.
 B=A;

  if (tourn && A>B-1.4)      % Test actif quand le robot tourne
        calllib('khepera3clib', 'SetSpeed',k3.id,50,-1);
 end
    
    if (tourn && A<=B-1.4)         % Test de fin de virage
         % Remet le robot en mode normal:
        calllib('khepera3clib', 'StopMotors',k3.id);
        k3.StartFollowLine(agr,vel);
        tourn=false;
    end
end


