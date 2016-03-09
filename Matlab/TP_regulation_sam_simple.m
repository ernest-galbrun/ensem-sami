%%% Essai simple avec regulation en vitesse le long de l'axe x
%%% On suppose theta=0, y=0



r = khepera3;
% Mode 1 : avec camera
% Mode 2 : sans camera
r.SetConnectionMode(1);
idx_robot = 5;
virtual_robot = false;
position_init = [-1000 100]; % utile uniquement en mode roue libre
% ou si les cameras ne voit pas le robot
r.Connect(idx_robot, virtual_robot, position_init)
% Mode de controle des moteurs (pour SetPoint)
% -> vitesse : 1
% -> vitesse : 1
r.SetMode(1,1);
lref = 0;
pref = 0;
ref = [lref; pref];

% Dynamique du moteur :
% dot(v) = -a*v+b*u
a = 0.050;  % temps de réponse du moteur
vl0 = 100;  % vitesse caractéristique (mm/s)
%b = 1;     % vitesse = b/a * consigne en régime continu

% Correction proportionelle
K = 10;

% Objectif
x0 = 0;

% consigne = 300 vitesse = 125 mm/s
% b/a = G = 125/300 = 0.4
d = 50; % 1/2 entraxe des roues
%P_inv = [0.5 0.5;
%         -d  d];   
tic
X = r.GetXYPosition;
Xarray = zeros(Tmax,2);
Tmax = 300;
t = 1;
l_prec = x(1);
theta_prec = r.GetOrientation;
while(true)
    dt = toc;
    while(dt<0.01)
        dt = toc;
    end
    tic
    X = r.GetXYPosition;
    Xarray(t,:) = X;
    x = X(1,1);
    l = X(1,1);
    y = X(1,2);
    theta = r.GetOrientation;
    v_theta = (theta - theta_prec)/dt;
    v_l = (l - l_prec) / dt;    
    erreur = (x0-x);
    % Consigne
    u = K*erreur;
    ug = u;
    ud = u;
    r.SetPoint(ug,ud);%commande(1), commande(2));
    l_prec = l;
    theta_prec = theta;
    if(t>=Tmax)
        break
    else
        t = t+1;
    end
end

r.SetPoint(0,0);%commande(1), commande(2));