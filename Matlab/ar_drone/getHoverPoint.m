function [ hoverPoint ] = getHoverPoint( W , zRef)
%getHoverPoint calcule le point indiqué par la baguette
%   En fonction du vecteur directeur de la baguette et d'un point de la
%   baguette, qui définit une droite dans l'espace, on va cherche
%   l'intersection entre cette droite et un plan à z=cste :  c'est là que
%   le drone doit rester aller

Vdir = W(1:3); % vecteur directeur
P = W(4:6); % point appartenant à la baguette

% calcul du point
k = Vdir(3)/(-P(3));
xRef = Vdir(1)/k+P(1);
yRef = Vdir(2)/k+P(2);
    if(isnan(xRef) || isnan(yRef))
        hoverPoint = [0, 0, zRef];
    else
        hoverPoint = [xRef, yRef, zRef];
    end
end

