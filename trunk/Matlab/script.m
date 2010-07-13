myRobot=khepera3()
myRobot.Connect(2,'193.49.136.176')
t=0:0.1:2*pi;
trajectory = sin(t);
T=zeros(size(trajectory));
O=T;
X=[T;T];
for i=1:length(trajectory)
    myRobot.SetVelocity(5,trajectory(i));
    t0=clock;
    T(i)=t0(6);
    X(:,i)=myRobot.GetXYPosition();
    O(i)=myRobot.GetOrientation();
    while etime(clock,t0)<.5
    end 
    
    
end

figure(1)
plot(T,O)
figure(2)
plot(X(1,:),X(2,:))
figure(3)
clf,hold on
plot(T,X(1,:),T,X(2,:))