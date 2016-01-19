function tab = Initialisation2(entree)
%   Cette fonction permet d'initialiser un tableau r�unisant les informations
% n�cessaires � la d�finition d'une trajectoire.
% * En entr�e, elle prend un vecteur de Khepera3 (par exemple : [r1, r2, r3], avec r1 = khepera3(1), ...).
% * La fonction renvoit un tableau sous cette forme :
%   t{n� robot , 1} : le khepera num�ro "n� robot".
%   t{n� robot , 2} : l'agressivit� du robot (par d�fault = 1).
%   t{n� robot , 3} : la vitesse (par d�fault = 5000).
%   t{n� robot , 4}(: , 1) : le vecteur des directions du robot.
%   t{n� robot , 4}(: , 2) : le vecteur des robots qui donne la priorit� (0 si il n'y a pas de priorit�).
%   t{n� robot , 4}(: , 3) : le vecteur des lecteur o� le robot doit attendre la priorit�.

s = '';

nb = numel(entree); % nombre de robots.

% On utilise un tableau de cellule (tab = {...}) afin de pouvoir ranger des
% types diff�rents au sein d'un m�me tableau.

def=' ';
while(def==' ')
    def = input('   Voulez-vous prendre les valeurs de vitesse et d agressivit� par d�fault (5000 et 1)? (O/N) : ','s');
    if(def~='O' && def~='o' && def~='N' && def~='n')
         disp('   Instruction erron�e'); disp(' ');
         def=' ';
    end
end


for j= 1:nb
    disp('--------------------');
    disp(['Robot ',num2str(j)]);
    tab{j , 1} = entree(j);
    
    if(def=='O' | def=='o')
        tab{j , 2} = 1;             % aggressivit� par d�fault.
        tab{j , 3} = 5000;          % vitesse par d�fault.
    else
        tab{j , 2} = input('Agressivit� : ');
        tab{j , 3} = input('Vitesse : ');
    end
       
    disp('Trajectoire : ');
    tab{j , 4} = Direction(entree(j),j);
    % On appelle cette fonction afin de lancer la proc�dure de d�finition de
    % virage � r�aliser.
end
return
end

function [te] = Direction(k3,robot)
% Cette fonction a pour but de simplifier la transmission d'un parcours au robot
S = '';s = '';
stop = false;
i = 1;
disp ('Gauche = G | Tout droit = T | Droite = D | Demi tour = O | Modifier pr�c�dent = M | Fin = F')
while (stop ~= true)
    disp (' ');
    disp (['�tape ', num2str((i+1)/2)]);
    comp=true;
    S = input('Direction suivante : (G/T/D/O/F) ','s');
    switch S
        case {'g','G'}
            te(1,i) = 2;
            
            
        case {'D','d'}
            te(1,i) = 1;
            
            
        case {'T','t'}
            te(1,i) = 0;
            
            
        case {'O','o'}
            te(1,i) = 3;
            
            
        case {'M','m'}
            i = i-2;
            
            if(i<=0)
                disp('impossible : �tape initial.')
                i=i+2;
            end
            comp=false;
            
            
        case {'F','f'}
            if(i==1)
                disp('impossible : aucune instruction.')
                
            else stop = true;
            end
            comp=false;
            
        otherwise
            disp('Instruction erron�e')
            comp=false;
    end
    
    if(comp)     % si une direction valide est donn�, on remplit le reste et on incr�mente i.
        te(1,i+1) = 0;               % le 0 en i+1 est la direction tout droit en lecteur de sortie de noeud.
        num= Priorite(robot);
        
        te(2,i) = num(1);
        te(2,i+1) = 0;
        te(3,i) = num(2);
        te(3,i+1) = 0;
        i = i+2;
    end
end
te = transpose(te); % attention � ce "d�tail" si vous voulez comprendre le fonctionnement en testant la matrice.

end


function num = Priorite(robot)
% Cette methode permet de conna�tre le lecteur de validation du passage
% du robot prioritaire.
R = ' '; s = ' '; T = ' ';
num = 0;
valid = false;
while (valid ~= true)
    %Cette boucle permet de reproposer la saisie tant que le caract�re ins�r� est erron�
    R = input('Conflit de Priorit� ? (O/N) ','s');
    switch R
        case {'O','o'}
            num(1)= input('Num�ro du robot prioritaire : ');
            if(num(1)==robot)
                disp('Impossible : un robot ne peut d�clencher sa propre autorisation.');
                
            else
                num(2) = input('Num�ro du lecteur de validation du passage du robot prioritaire : ');
                valid = true;
            end
            
        case {'N','n'}
            num = [0,0];
            valid = true;
            
        otherwise
            disp('Instruction erron�e');
    end
end
end