function [res] = Recherche(k3,j,X)
res=0;
for i=1:numel(X)
    
    if(X(i)==j)
        res=i;
        break;
    end
    
end

end

