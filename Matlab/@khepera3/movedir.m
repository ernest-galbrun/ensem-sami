function [t,D,O,V]=movedir(O,D,A,V,dx,dy,t) %fonction qui fait tourner à gauche ou à droite (dépend de l'orientation)
k=real(dx*dy*O^2);%On doit prendre la partie réelle de l'expression dx*dy*O^2 (permet de déterminer s'il faut aller à gauche ou à droite)
%car par exemple si O=i dx=dy=1 MATLAB considère 1*1*i^2=-1 comme un complexe à partie imaginaire nulle et il y a erreur lorsqu'on compare à 0.
if (k>0)
    t=[t;2];D(1)=D(1)+dx;D(2)=D(2)+dy;O=1i*O;V=[V;D];%disp('gauche');disp('position :');disp(D);
else
    t=[t;1];D(1)=D(1)+dx;D(2)=D(2)+dy;O=-1i*O;V=[V;D];%disp('droite');disp('position :');disp(D);
end
end