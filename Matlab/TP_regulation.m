
r = khepera3;
r.SetConnectionMode(1);
r.Connect(5, false, [-1000 100])
r.SetMode(1,1);
lref = 0;
pref = 0;
ref = [lref; pref];

% Dynamique du moteur :
% dot(v) = -a*v+b*u
a = 0.050;  % temps de réponse du moteur
vl0 = 100;  % vitesse caractéristique (mm/s)
%b = 1;     % vitesse = b/a * consigne en régime continu

% consigne = 300 vitesse = 125 mm/s
% b/a = G = 125/300 = 0.4
G = 0.4;
b = G*a;
A = [0 0   1  0 0;
     0 0   0  1 0;
     0 0  -a  0 0;
     0 0   0 -a 0;
     0 vl0 0  0 0];
 B = [0 0;
      0 0;
      b 0;
      0 b;
      0 0];
  
ksi = 0.7; % facteur d'amortissement
tr = 10;
omega_n = 3.3/tr;
%syms s
%solve (1+2*ksi/omega_n*s + s*s/(omega_n*omega_n)==0)
delta = (2/omega_n)^2 * (ksi*ksi -1);
s1 = (-1*2*ksi/omega_n + 1i*sqrt(-1*delta))/2;
s2 = (-1*2*ksi/omega_n - 1i*sqrt(-1*delta))/2;
K = place(A,B,[-12, -11, -10, s1, s2]);
C = [1 0 0 0 0;
     0 0 0 0 1];  % Y = CX
M = A - B*K;
F = inv(-C* inv(M) * B);
d = 50; % 1/2 entraxe des roues
%P_inv = [0.5 0.5;
%         -d  d];   
P_inv = [-1/(2*d)  1/(2*d);
    0.5 0.5];   
P = inv(P_inv); 
tic
x = r.GetXYPosition;
l_prec = x(1);
theta_prec = r.GetOrientation;
while(true)
    dt = toc;
    while(dt<0.01)
        dt = toc;
    end
    tic
    x = r.GetXYPosition;
    l = x(1);
    p = x(2);
    theta = r.GetOrientation;
    v_theta = (theta - theta_prec)/dt;
    v_l = (l - l_prec) / dt;
    X = [l; theta; v_l; v_theta; p];
    u = F*ref - K *X;
    commande = P * (u .* [1e-3;1e-2])
    r.SetPoint(commande(1), commande(2));
    l_prec = l;
    theta_prec = theta;
end