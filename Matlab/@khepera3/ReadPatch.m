function X= ReadPatch()

c=tcpip('193.49.136.247',502);
fopen(c);
fwrite(c,uint8([0 0 0 0 0 6 1 4 hex2dec('10') hex2dec('26') 0 1]),'uint8');
X=fread(c,11);
X(10)
X(11)
fclose(c);
end