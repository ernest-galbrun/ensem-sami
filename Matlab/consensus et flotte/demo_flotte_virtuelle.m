N=15
R = KheperaFleet(N);
id = 10+(1:N);
size = 10000;
initpos = 500000 + (rand(N,2)*size*2 - size);
initorientation = rand(N,1) * 2 * pi;
error = R.ConnectF(id,ones(N,1),initpos,initorientation);
[X Y] = R.GetPositionF;
thresold = 7000;
for i=1:N
for j=1:N
if i~=j && norm([X(i) Y(i)] - [X(j) Y(j)]) < thresold %distance bw i and j
A(i,j)=1;
end
end
end
R.DefineNetwork('manual',A)
R.FleetFormation(1,'circle',5000,0)