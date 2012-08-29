function RendezVous_Static_TurnAndGo(KheperaFleet,VlinMax,VangMax,EpsiAng,FinalRadius)

% Initialization
global t1;
global t2;
global preD;
global test1;
global pre2D;
global etat;
etat = zeros(KheperaFleet.NumberOfKhepera,1);
test1 = zeros(KheperaFleet.NumberOfKhepera,1);
preD = 10^5*ones(KheperaFleet.NumberOfKhepera,1);
pre2D = 10^5*ones(KheperaFleet.NumberOfKhepera,1)+1000;

t1 = timer('Name','Timer-angle','Period',0.01,'ExecutionMode','fixedSpacing','TasksToExecute',Inf);
t2 = timer('Name','Timer-position','Period',0.01,'ExecutionMode','fixedSpacing','TasksToExecute',Inf);

[RealXPosition RealYPosition] = KheperaFleet.GetPositionF;
TheoXPosition = RealXPosition; 
TheoYPosition = RealYPosition;
Phi = KheperaFleet.GetOrientationF;
A = KheperaFleet.Network;
Radius = FinalRadius;
VlinM = VlinMax;
VangM = VangMax;
EpsiA = EpsiAng*2*pi/360;
EveryAgentIsHere = WhoIsHere([RealXPosition RealYPosition],Radius);

disp('Start of consensus');
i=1;
while(any(not(EveryAgentIsHere)))

    B =  BaryGraph(RealXPosition(:,i),RealYPosition(:,i),A);
    TheoXPosition(:,i+1) =B(:,1);
    TheoYPosition(:,i+1) =B(:,2);
    Phi(:,i+1) = InWhichDirection([RealXPosition(:,i) RealYPosition(:,i)],[TheoXPosition(:,i+1) TheoYPosition(:,i+1)]);
    EpsiP = distance([RealXPosition(:,i) RealYPosition(:,i)],[TheoXPosition(:,i+1) TheoYPosition(:,i+1)]).*tan(EpsiA);
    

GoalAngle = [Phi(:,i+1) Phi(:,i+1)*360/(2*pi)]
% Step 1 : Turning agents
disp('Starting turning phase');
set(t1,'TimerFcn',{@UpdateOrientation,KheperaFleet,Phi,i,VangM,EpsiA});
start(t1);
while(strcmp(t1.Running,'on'))
end
stop(t1)
disp('End of turning phase');
FinalAngle = [KheperaFleet.GetOrientationF KheperaFleet.GetOrientationF*360/(2*pi)]


% Step 2 : Go straight to the point!
disp('Starting phase2');
set(t2,'TimerFcn',{@UpdatePosition,KheperaFleet,TheoXPosition,TheoYPosition,i,VlinM,EpsiP});
start(t2)
while(strcmp(t2.Running,'on'))
end
stop(t2)
[RealXPosition(:,i+1) RealYPosition(:,i+1)] = KheperaFleet.GetPositionF;
TheoXPosition(:,i+2) =RealXPosition(:,i+1);
TheoYPosition(:,i+2) = RealYPosition(:,i+1);

disp('End of phase 2');
IsTooFar([RealXPosition(:,i+1) RealYPosition(:,i+1)],[TheoXPosition(:,i+1) TheoYPosition(:,i+1)],EpsiP);
EveryAgentIsHere = WhoIsHere([RealXPosition RealYPosition],Radius);
% break;
    i=i+1;
    if(i>50)
        break;
    end
end
disp('End of consensus');
delete(t1)
delete(t2)

figure (1)
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
    plot(TheoXPosition(:,k),TheoYPosition(:,k),'b.');
end

for k=1 : size(RealXPosition,2)-1
    for j = 1:KheperaFleet.NumberOfKhepera
    plot([TheoXPosition(j,k+1) TheoXPosition(j,k)],[TheoYPosition(j,k+1) TheoYPosition(j,k)],'c');
    plot([RealXPosition(j,k+1) RealXPosition(j,k)],[RealYPosition(j,k+1) RealYPosition(j,k)],'r');
    end
end


figure (2)
for k=1:KheperaFleet.NumberOfKhepera
plot([1:1:size(RealXPosition,2)],RealXPosition(k,:));
end
hold off