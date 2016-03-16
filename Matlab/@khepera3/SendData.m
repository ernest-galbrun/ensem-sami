function SendData(k3,value)

c=tcpip('193.49.136.247',502);
fopen(c);

% good trame
Trame=uint8([9 101 1 35 0 value 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 6]);
 
%test=uint8([0 0 0 0  0 9 1 16 18 185 0 1 2 0 1])
%test2=uint8([0 0 0 0  0 6 1 6 17 211 95 36])
 
%good trame
Trame_request=uint8([0 0 0 0 0 43 1 16 18 185 0 18 36 Trame]);
fwrite(c,Trame_request,'uint8');
fread(c,12);

%good trame
Trame_response=uint8([0 0 0 0 0 6 1 4 18 204 0 18]);
fwrite(c,Trame_response,'uint8');
fread(c,45)
 
end