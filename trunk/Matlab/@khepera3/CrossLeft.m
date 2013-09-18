function CrossLeft(k3,agr,vel)
StartFollowLine(k3,agr,vel);
V=k3.GetIRProximity;
while (V(10)<3900||V(11)<3900)
    V=k3.GetIRProximity;
end
StopFollowLine(k3);
TurnLeft(k3,agr,vel);
end

