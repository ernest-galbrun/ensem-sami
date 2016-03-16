function [X] = appelpatch(k3,c)

fwrite(c,uint8([0 0 0 0 0 6 1 4 16 33 0 1]),'uint8');
t=fread(c,11);
X(1)=t(11);
fwrite(c,uint8([0 0 0 0 0 6 1 4 16 38 0 1]),'uint8');
t=fread(c,11);
X(2)=t(11);
fwrite(c,uint8([0 0 0 0 0 6 1 4 16 43 0 1]),'uint8');
t=fread(c,11);
X(3)=t(11);
fwrite(c,uint8([0 0 0 0 0 6 1 4 16 48 0 1]),'uint8');
t=fread(c,11);
X(4)=t(11);


end

% Cette fonction doit être mise à jour à chaque nouveau lecteur installé
% afin qu'il soit pris en compte dans le programme.