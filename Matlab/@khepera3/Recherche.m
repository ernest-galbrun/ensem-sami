function [res] = Recherche(k3,j,X)

%Cette fonction permet de trouver gr�ce au tableau g�n�r� par la fonction
%appelpatch un patch parmi les lecteurs et renvoie le lecteur qui a d�tect�
%le patch recherch�

res=0;
for i=1:numel(X)
    
    if(X(i)==j)
        res=i;
        break;
    end
    
end

end

