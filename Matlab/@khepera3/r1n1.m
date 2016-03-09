function [ fin ] = r1n1( k3,dir,agr,vel )
c=tcpip('193.49.136.247',502);
fopen(c);
k3.StartFollowLine(agr,vel);
X(1)=0; X(2)=0;
fin=0;
test1=true;

while(X(1)~=1)
    fin=fin+1;
    X=appelpatch(k3,c);   
    
    if(X(2)==1 & test1)
        test1=false; k3.StopFollowLine; k3.Cross(dir,agr,vel);
    end
    
    
    
end

k3.StopFollowLine;
return;

end

