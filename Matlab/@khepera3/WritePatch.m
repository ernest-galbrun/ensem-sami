function [ X ] = WritePatch()
c=tcpip('193.49.136.247',502);
fopen(c);
fwrite(c,uint8([0 0 0 0  0 8 1 6 hex2dec('11') hex2dec('D0') 0 0 0 1]),'uint8');
X=fread(c,13);
X(10)
X(11)
X(12)
X(13)
fclose(c);
end

