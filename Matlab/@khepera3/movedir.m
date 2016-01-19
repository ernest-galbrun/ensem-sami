function [t,D,O,V]=movedir(O,D,A,V,dx,dy,t) %fonction qui fait tourner � gauche ou � droite (d�pend de l'orientation)
k=real(dx*dy*O^2);%On doit prendre la partie r�elle de l'expression dx*dy*O^2 (permet de d�terminer s'il faut aller � gauche ou � droite)
%car par exemple si O=i dx=dy=1 MATLAB consid�re 1*1*i^2=-1 comme un complexe � partie imaginaire nulle et il y a erreur lorsqu'on compare � 0.
if (k>0)
    t=[t;2];D(1)=D(1)+dx;D(2)=D(2)+dy;O=1i*O;V=[V;D];%disp('gauche');disp('position :');disp(D);
else
    t=[t;1];D(1)=D(1)+dx;D(2)=D(2)+dy;O=-1i*O;V=[V;D];%disp('droite');disp('position :');disp(D);
end
end