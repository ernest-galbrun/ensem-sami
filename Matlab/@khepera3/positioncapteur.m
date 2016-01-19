function [O] = positioncapteur( k3,a )
%Cette fonction permet, à partir du numéro du capteur, d'avoir ses
%coordonnées
%   SI VOUS RAJOUTEZ DES CAPTEURS, PENSEZ A MODIFIER LA LISTE DES POSITIONS
%   DE CAPTEURS !
switch a
    case{1}
            O=[6 1];
    case{2}
            O=[7 2];
    case{3}
            O=[6 3];
    case{4}
            O=[5 2];
    case{5}
            O=[6 5];
    case{6}
            O=[7 6];
    case{7}
            O=[5 6];
end
end

