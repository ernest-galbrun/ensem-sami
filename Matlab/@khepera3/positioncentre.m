function O= positioncentre( a )
%A partir du numéro du noeud, on obtient sa position sur le quadrillage
%   A CHAQUE RAJOUT DE NOEUD, METTRE A JOUR LES SWITCHS !
 switch a
        case{1}
            O=[6 2];
        case{2}
            O=[6 5];
 end
end

