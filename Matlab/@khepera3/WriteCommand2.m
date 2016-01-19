function [ Trame ] = WriteCommand2( slave, val)

%Cette fonction ex�cute la fonction d'�criture de registre (num�ro 35)
%contrairement � WriteCommand qui propose � l'utilisateur de choisr sa
%commande � envoyer

Trame = uint8(zeros(1,34));
Trame(1) = slave; %slave number
Trame(2) = 35; % #23 command id
Trame(3:4) = [0 1]; %"write tag" command
Trame(5:6) = [0 val]; %value written
Trame(7:8) = [0 val];
Trame(9:10) = [0 val];
Trame(33:34) = [0 4]; %number of bytes sent to slave

end

