function [ n ] = AppelNoeud( k3,V )
%Fonction qui renvoie le n� du noeux associ� � la coordon�e du capteur.
%Ex  [5 2] => 1    ou  [6 7]=>  2   
%En cas de coordonn�e fausse [6 8] => 0


n=0;
N=Noeuds();
for i=1:length(N)
    for j=1:length(N{:,i})
        W=N{:,i};
        if (isequal(V,[W(j,1) W(j,2)]))
            n=i;
        end
    end
end
if (n==0)
    disp('Instruction erron�e dans AppelNoeud'); disp(' ');
end

