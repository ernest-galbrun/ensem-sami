function Flocking(KheperaFleet,Vlin,time)

KheperaFleet.SetVelocityF(Vlin,zeros(KheperaFleet.NumberOfKhepera,1)); %initialisation de la vitesse

A = KheperaFleet.Network; %Adjacency matrix
Phi = KheperaFleet.GetOrientationF;%Current orientation

% Initialisation de paramètre
thresholdV = 2; %Seuil de vitesse
thresholdA = 0.1*2*pi/360; %Seuil d'angle
p=1;


t = InTheSameDirection(Phi,thresholdA); %Initialisation
s = WithTheSameSpeed(Vlin,thresholdV);  %Initialisation


% Matrice de degres
D = diag(A*ones(KheperaFleet.NumberOfKhepera,1));

% Laplacian matrix
L = D-A;

epsi = 0.3;

%matrice de Perron
P = eye(KheperaFleet.NumberOfKhepera)-epsi*L;

NewSpeed=Vlin; %initialisation

while(not(t) && any(not(s))) %On sort quand on atteint le consensus en vitesse & angle

disp('la')
NewAngle = P*Phi;%((Phi+A*Phi)./(sum(A(:,:))'+1)); %Consensus en angle



NewSpeed = P*NewSpeed; %Consensus en vitesse



KheperaFleet.ChangeAngleAndSpeed(NewAngle,NewSpeed,time); %permet de modifier l'angle et la vitesse

%pause(0.2)

Phi = KheperaFleet.GetOrientationF; %reactualisation des Angles

t = InTheSameDirection(Phi,thresholdA); %Critere de test
s = WithTheSameSpeed(NewSpeed,thresholdV); %Critere de test

p=p+1;

[CPX(:,p) CPY(:,p)] = KheperaFleet.GetPositionF; %permet de tracer la position


%% Trace les robots
for i=1:size(A,1)
    
    if(p==2)
        plot(CPX(i,:),CPY(i,:),'r+')
    else
    plot(CPX(i,:),CPY(i,:),'b+')
    hold on
    end
  
end

%% Critère d'arret par defaut (au cas ou)
    if(p>50)
        break;
    end
    
end
p; % Permet de connaitre le nombre d'itération


end

