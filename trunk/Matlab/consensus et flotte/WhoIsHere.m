function Answer = WhoIsHere(CurrentPosition,Radius)
n = size(CurrentPosition,1);
x = CurrentPosition(:,1);
y = CurrentPosition(:,2);
bx = sum(x)/n;
by = sum(y)/n;


Answer = zeros(n,1);

d = distance([CurrentPosition(:,1) CurrentPosition(:,2)],[bx*ones(n,1) by*ones(n,1)]);
Answer(:,1) = d(:,1)<Radius;

end