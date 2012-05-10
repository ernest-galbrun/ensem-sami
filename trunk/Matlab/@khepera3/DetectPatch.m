function DetectPatch(k3)

c=tcpip('193.49.136.247',502);
fopen(c);

while true
    fwrite(c,uint8([0 0 0 0  0 6 1 4 hex2dec('10') hex2dec('21') 0 1]),'uint8');
    X=fread(c,11);
    val=X(10)*256;

    if val==32000 
        k3.StopMotors;
        break
    end

end


end
