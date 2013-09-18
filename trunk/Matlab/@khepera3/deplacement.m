function  ts=deplacement( k3,agr,vel,te )
k3.StartFollowLine(agr,vel);
c=tcpip('193.49.136.247',502);
fopen(c);
a=0;
tc=30;

for i=1:6
    a=0;
    while(a~=1)
        tc=tc+1;
        a=0;
     fwrite(c,uint8([0 0 0 0  0 6 1 4 16 33 0 1]),'uint8');
    X1=fread(c,11);
    fwrite(c,uint8([0 0 0 0  0 6 1 4 16 38 0 1]),'uint8');
    X2=fread(c,11);
    fwrite(c,uint8([0 0 0 0  0 6 1 4 16 43 0 1]),'uint8');
    X3=fread(c,11);
    val=X1(10)+X2(10)+X3(10);
    

    if (val==125&& tc>2000)
        if (te(i)==10)
           
            CrossLeft(k3,agr, vel);
            StartFollowLine(k3,agr, vel);
        else if (te(i)==01)
               CrossRight2(k3,agr, vel);
            StartFollowLine(k3,agr, vel);
            end
        end
        if (X1(10)==125)
            ts(i)=33;
        else if (X2(10)==125)
                ts(i)=38;
            end
        end
        a=1;
    end
    
    end       

end
end

