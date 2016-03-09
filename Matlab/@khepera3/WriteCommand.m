function [Trame] = WriteCommand(k3,command,slave, val)

Trame = uint8(zeros(1,34));
Trame(1) = slave; %slave number
Trame(2) = command; % 35 écriture 34 lecture #23 command id
Trame(3:4) = [0 1]; %"write tag" command
Trame(5:6) = [0 val]; %value written
Trame(33:34) = [0 4]; %number of bytes sent to slave

end

