function  ts=dpl( k3,agr,vel,dir )
ts=0;
k3.StartFollowLine(agr,vel); 
c=tcpip('193.49.136.247',502);%Etablissement de la connection
fopen(c);
X(1)=0; X(2)=0; X(3)=0;
longueur_dir = numel(dir);
for i=1:longueur_dir
    test(i)=true; %Sert à ne prendre en compte la détection de chaque lecteur qu'une seule fois
end
i=1;
a=0;


while(i<=longueur_dir)
 X=appelpatch(k3,c); % X est un tableau contenant ce que chaque lecteur détecte
    
    if((X(1)==1||X(2)==1||X(3)==1) && test(i))%Condition : arrivée au noueud suivant 
        test(i)=false; 
        k3.StopFollowLine;  %Arrêt
        k3.Cross(dir(i),agr,vel); i=i+1;%Virage
    end
    
    
   
    
end
k3.StartFollowLine(agr,vel);
return
end

%Fonction servant à donner une série de directions à un robot.
% Le robot ne prendra le virage qu'après avoir été détecté par un lecteur.
%dir : vecteur contenant la suite des différentes directions que le robot prendra.



