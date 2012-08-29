function RDV_Static(KheperaFleet,FinalRadius,tau,stop)

[RealXPosition RealYPosition] = KheperaFleet.GetPositionF;

A = KheperaFleet.Network;
Radius = FinalRadius;

N = size(A,1);
Ze = zeros(N,1);


% Matrice de degres
D = diag(KheperaFleet.Network*ones(N,1));
% Laplacian matrix
L = D-KheperaFleet.Network;
epsi = 0.3;
P = eye(KheperaFleet.NumberOfKhepera)-epsi*L;


disp('Start of consensus');

% Consensus
% EveryAgentIsHere = WhoIsHere([TheoXPosition(:,1) TheoYPosition(:,1)],Radius/10);
% i=1;
% while(any(not(EveryAgentIsHere)))
%     %       Autre consensus
% %     B =  BaryGraph(RealXPosition(:,i),RealYPosition(:,i),A);
% % TheoXPosition(:,i+1) =B(:,1);
% %TheoYPosition(:,i+1) =B(:,2);
%     TheoXPosition(:,i+1) =P*TheoXPosition(:,i);
%     TheoYPosition(:,i+1) =P*TheoYPosition(:,i);
%     EveryAgentIsHere = WhoIsHere([TheoXPosition(:,i+1) TheoYPosition(:,i+1)],Radius/10);
%     i=i+1;
% end


EveryAgentIsHere = WhoIsHere([RealXPosition(:,1) RealYPosition(:,1)],Radius);
i=1;
while(any(not(EveryAgentIsHere)))
    % Algorithme de consensu
    TX =P*RealXPosition(:,i);
    TY =P*RealYPosition(:,i);
    
KheperaFleet.GoTo([TX TY],tau,1,stop);
[RealXPosition(:,i+1) RealYPosition(:,i+1)] = KheperaFleet.GetPositionF;
EveryAgentIsHere = WhoIsHere([RealXPosition(:,i+1) RealYPosition(:,i+1)],Radius);
% break;
    i=i+1;
if(all(abs(RealXPosition(:,i)-RealXPosition(:,i-1))<1 & abs(RealYPosition(:,i)-RealYPosition(:,i-1))<1));
    break;
end
end
disp('End of consensus');
KheperaFleet.SetVelocityF(Ze,Ze);
figure (2)
hold on

for k=1:KheperaFleet.NumberOfKhepera
    for p = k:KheperaFleet.NumberOfKhepera
    if(KheperaFleet.Network(k,p)==1)
        plot([RealXPosition(k,1) RealXPosition(p,1)],[RealYPosition(k,1) RealYPosition(p,1)],'g');
    end
    end
end


for k=1:size(RealXPosition,2)
    plot(RealXPosition(:,k),RealYPosition(:,k),'ro');
%     plot(TheoXPosition(:,k),TheoYPosition(:,k),'b.');
end
% 
% for k=1 : size(RealXPosition,2)-1
%     for j = 1:KheperaFleet.NumberOfKhepera
%     plot([TheoXPosition(j,k+1) TheoXPosition(j,k)],[TheoYPosition(j,k+1) TheoYPosition(j,k)],'c');
%     plot([RealXPosition(j,k+1) RealXPosition(j,k)],[RealYPosition(j,k+1) RealYPosition(j,k)],'r');
%     end
% end


figure (3)
for k=1:KheperaFleet.NumberOfKhepera
plot([1:1:size(RealXPosition,2)],RealXPosition(k,:));
hold on
end
hold off