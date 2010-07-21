%  myRobot=khepera3()
%  myRobot.Connect(2,'193.49.136.176')
t=0:0.1:2*pi;
trajectory = sin(t);
T=zeros(size(trajectory));
O=T;
X=[T;T];
tmax=0;
for i=1:length(trajectory)
    t0=clock;
    tic
    myRobot.SetVelocity(10,trajectory(i));
    % myRobot.SetVelocity(,trajectory(i));
    toc
    tic
    T(i)=t0(6);
    X(:,i)=myRobot.GetXYPosition();
    toc
    tic
    O(i)=myRobot.GetOrientation();
    toc
    tmax=max(tmax,etime(clock,t0));
    
    
    %comp=0;
    while etime(clock,t0)<.2
    %    comp=comp+1;
    end 
    %comp
    
end
%tmax
figure(1)
stairs(T,O)
figure(2)
plot(X(1,:),X(2,:))
figure(3)
clf,hold on
stairs(T,X(1,:))
stairs(T,X(2,:))
myRobot.SetVelocity(0,0);