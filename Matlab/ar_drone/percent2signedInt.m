function [out] = percent2signedInt(in)
%Conversion d'un float en entier non signé au sens binaire
hex=num2hex(single(in));
bin=zeros(32,1);
for i=1:8
   switch hex(i)
       case 'f',
           bin(1+4*(i-1):4*i)=[1 1 1 1];
       case 'e',
           bin(1+4*(i-1):4*i)=[1 1 1 0];
       case 'd', 
           bin(1+4*(i-1):4*i)=[1 1 0 1];
       case 'c', 
           bin(1+4*(i-1):4*i)=[1 1 0 0];
       case 'b', 
           bin(1+4*(i-1):4*i)=[1 0 1 1];
       case 'a',                
           bin(1+4*(i-1):4*i)=[1 0 1 0];
       case '9', 
           bin(1+4*(i-1):4*i)=[1 0 0 1];
       case '8',
           bin(1+4*(i-1):4*i)=[1 0 0 0];
       case '7', 
           bin(1+4*(i-1):4*i)=[0 1 1 1];
       case '6', 
           bin(1+4*(i-1):4*i)=[0 1 1 0];
       case '5', 
           bin(1+4*(i-1):4*i)=[0 1 0 1];
       case '4', 
           bin(1+4*(i-1):4*i)=[0 1 0 0];
       case '3', 
           bin(1+4*(i-1):4*i)=[0 0 1 1];
       case '2', 
           bin(1+4*(i-1):4*i)=[0 0 1 0];
       case '1',
           bin(1+4*(i-1):4*i)=[0 0 0 1];
       case '0', 
           bin(1+4*(i-1):4*i)=[0 0 0 0];
   end
end

bin=flipud(bin);
out=-bin(32)*2^(31);
for i=1:31
    out = out + bin(i)*2^(i-1);
end
end

