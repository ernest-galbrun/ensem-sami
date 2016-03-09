function [ X ] = ReadRegister(k3,c,adress,nb)

%l'identifiant 4 4 (arbitraire) pour reconnaitre l'opération de lecture
Trame=uint8([0 0 0 0 0 6 1 4 0 0 0 nb]);
Trame(9:10)=adress;

fwrite(c,Trame);
X=fread(c,9+2*nb);

end

