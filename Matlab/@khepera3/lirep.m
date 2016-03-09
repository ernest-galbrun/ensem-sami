function [X] = lirep(k3)
%lire un patch
c=tcpip('193.49.136.247',502);
fopen(c);

%good trame 
%Trame=uint8([1 101 4 34 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4]);
 
%good trame 
%Trame_request=uint8([0 0 0 0 0 43 1 16 18 185 0 18 36 Trame]);
%fwrite(c,Trame_request,'uint8');
%fread(c,12);

%good trame 
%Trame_response=uint8([0 0 0 0 0 6 1 3 18 204 0 18]);
%fwrite(c,Trame_response,'uint8');
%X=transpose(fread(c,45));

fwrite(c,uint8([0 0 0 0 0 6 1 4 16 48 0 5]),'uint8');
X=fread(c,19);

    
end

