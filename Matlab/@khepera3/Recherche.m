function [res] = Recherche(k3,j,X)

%Cette fonction permet de trouver grâce au tableau généré par la fonction
%appelpatch un patch parmi les lecteurs et renvoie le lecteur qui a détecté
%le patch recherché

res=0;
for i=1:numel(X)
    
    if(X(i)==j)
        res=i;
        break;
    end
    
end

end

