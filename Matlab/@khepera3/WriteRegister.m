function [ k ] = WriteRegister(k3,c,adresse,trame)

nt=numel(trame);
X=uint8(zeros(1,nt+11));

%[16 16, 0 0 ,0 compteur, cannal ,commande d'�criture, adresse ,compteur, Trame]

X(12:nt+11)=trame;
X(11)= nt;%nombre d'octet (<255)
X(9:10)=adresse;%sur 2 octets � convertir et doit �tre un tableau
X(8)=16; %commande d'�criture
X(7)=1;%numero du maitre
X(5:6)=[0 nt+5];%compteur
X(1:2)=[16 16];%pour signaler une commande d'�criture (arbitraire)


fwrite(c,X);
k=fread(c,12);

end

