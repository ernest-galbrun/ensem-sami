function DTRight(k3,agressivity,velocity)
A=k3.GetOrientation;
B=A;
calllib('khepera3clib', 'StartMotors',k3.id);

while A>B-3.14
  calllib('khepera3clib', 'SetSpeed',k3.id,0.5,-0.7);
  A=k3.GetOrientation;
end
  calllib('khepera3clib', 'StopMotors',k3.id);
  k3.StartFollowLine(agressivity,velocity);
end