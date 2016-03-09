function [j] = r2lignecommune( k3,k2,agr,vel, dir,p )

c=tcpip('193.49.136.247',502);%Etablissement de la connection
fopen(c);
k3.StartFollowLine(agr,vel);
k2.StartFollowLine(agr,vel);
fin=true;
% for i=1:numel(dir(1,:))
%     test(1,i)=true; test(2,i)=true;
% end

i=1;j=1;


while(fin)
    X=appelpatch(k3,c);
    
    if((X(1)==1||X(2)==1||X(3)==1))% && test(1,i))%Condition : arrivée au noueud suivant
%         test(1,i)=false;
        % k3.StopFollowLine;  %Arrêt
        % k3.Cross(dir(i),agr,vel); i=i+1;%Virage
    end
    
    if((X(1)==2||X(2)==2||X(3)==2)) %&& test(2,j))
        k2.StopFollowLine;
        
        if(p(j)==0 )
%             test(2,j)=false;
            k2.Cross(dir(2,j),agr,vel);
        end
    end
    
%     Z=GetIRProximity(k2);
%     
%     if(Z(10)>3800 && Z(11)>3800 && test(2,j)==false)
%     j=j+1;
%     end
    
    p=Auto(k3,j,X,p,1);
    
    
    
    if(X(4)>0 | j>5)
        fin=false;
    end
    
end
k2.StopFollowLine;
k3.StopFollowLine;
return
end

