function [ val ] = ReadPatch(k3,slave)
%Sert à lire un patch avec un esclave 

c=tcpip('193.49.136.247',502);
fopen(c);

T=k3.ReadRegister(c,[16 28+5*slave],1);
val=T(11);

end
