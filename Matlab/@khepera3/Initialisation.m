function tab = Initialisation(entree)
%Cette fonction permet d'initialiser un tableau réunisant les informations
%nécessaires à la définition d'une trajectoire.

s = '';
nb = numel(entree);

% On utilise un tableau de cellule (tab = {...}) afin de pouvoir ranger des
% types différents au sein d'un même tableau

for j= 1:nb
    disp('--------------------');     
    str = ['Robot ',num2str(j)];
    disp(str);
    tab{j , 1} = entree(j); 
    tab{j , 2} = input('Agressivité : ');
    tab{j , 3} = input('Vitesse : ');
    disp('Trajectoire : ');
    tab{j , 4} = Direction(entree(j)); 
    %On appelle cette fonction afin de lancer la procédure de définition de
    %virage à réaliser.
end
return 
end

function [te] = Direction(k3)
%Cette fonction a pour but de simplifier la transmission d'un parcours au robot
S = '';s = '';
R = 0;
stop = false;
i = 1;
disp ('Gauche = G | Tout droit = T | Droite = D | Demi tour = O | Modifier précédent = M | Fin = F')
while (stop ~= true)
    disp (' ');
    S = input('Direction suivante : (G/T/D/O/F) ','s');
    switch S
        case {'g','G'}
            te(1,i) = 2;
            te(1,i+1) = 0;
            te(2,i) = Priorite();
            te(2,i+1) = 0;
            i = i+2; 
       
        case {'D','d'}
            te(1,i) = 1;
            te(1,i+1) = 0;
            te(2,i) = Priorite();
            te(2,i+1) = 0;
            i = i+2;
        
        case {'T','t'}
            te(1,i) = 0;
            te(1,i+1) = 0;
            te(2,i) = Priorite();
            te(2,i+1) = 0;
            i = i+2;
                    
        case {'O','o'}
            te(1,i) = 3;
            te(1,i+1) = 0;
            te(2,i) = Priorite();
            te(2,i+1) = 0;
            i = i+2;
             
        case {'M','m'}
             R = input('Précisez la nouvelle direction : Gauche = 2 | Tout Droit = 0 | Droite = 1 | Demi tour = 3 : ');
            te(1,i-2) = R;
            te(1,i-1) = 0;
            te(2,i-2) = Priorite();
            te(2,i-1) = 0;
            i = i+2;
            
        case {'F','f'}
            stop = true;       
            
        otherwise
            disp('Instruction erronée')
    end
    
end
te = transpose(te);

end


function num = Priorite()
% Cette methode permet de connaître le lecteur de validation du passage
% du robot prioritaire.
R = ' '; s = ' '; T = ' ';
num = 0;
valid = false;
while (valid ~= true)
    %Cette boucle permet de reproposer la saisie tant que le caractère inséré est erroné
    R = input('Conflit de Priorité ? (O/N) ','s');
    switch R
        case {'O','o'}
            num = input('Numéro du lecteur de validation du passage du robot prioritaire : ');
            valid = true;      
            
        case {'N','n'}
            num = 0;
            valid = true;
       
        otherwise
            disp('Instruction erronée');
            valid = false;            
    end
end
end
