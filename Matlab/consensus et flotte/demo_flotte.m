%Ip = '193.49.136.189';
%N=input('nombre de robots : ');
N=3
R = KheperaFleet(N)
R.SetConnectionModeF(1);
%error=R.ConnectF([3;4;5],[0,0,0,0],[0 0;0 1500;700 3000;1800 1500],[3*pi/2;0;pi/2;pi])
error=R.ConnectF([4;7;6],[0,0,0],[0 0;0 0;0 0],[0;0;0])


[X Y] = R.GetPositionF;
A = zeros(N,N);
thresold = 1000;
for i=1:N
    for j=1:N
        if i~=j && norm([X(i) Y(i)] - [X(j) Y(j)]) < thresold %distance bw i and j
            A(i,j)=1;
        end
    end
end

disp('network');
R.DefineNetwork('manual',A)


%disp('flocking')
%R.Flocking(80*[1;1.5;1.2;1.2;0.8],1.5);



%R.RDV_Static(10,0.5,0)
%R.FleetFormation(1,'circle',1000,0)
%R.FleetFormation(2,'line',[2 1000],0)