function [ a ] = AppelCapteur( k3,u )
%RETURNNUMCAPTEUR est une fonction qui retoune le n° du
%capteur(1,2,3,...,8) en fonction de ses coordonnées ([6 1],....[5 6])
a=0;
if (isequal(u,[6 1]))
    a=1;
else
    if (isequal(u,[7 2]))
        a=2;
    else
        if (isequal(u,[6 3]))
            a=3;
        else
            if (isequal(u,[5 2]))
                a=4;
            else
                if (isequal(u,[6 5]))
                    a=5;
                else
                    if (isequal(u,[7 6]))
                        a=6;
                    else
                        if (isequal(u,[5 6]))
                            a=7;
                            %else
                                %disp('Instruction erronée dans AppelCapteur'); disp(' ');
                            end
                        end
                    end
                end
            end
        end
    end
end



