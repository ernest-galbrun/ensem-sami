function [ x ] = detection(  )

c=tcpip('193.49.136.247',502);
fopen(c);

Trame_response=uint8([0 6 0 0 0 6 1 4 16 33 0 6]);
fwrite(c,Trame_response,'uint8');
x=transpose(fread(c,19));


end

