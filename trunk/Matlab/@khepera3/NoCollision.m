function NoCollision(k3)
V=k3.GetIRProximity

while true
    V=k3.GetIRProximity;
   
        if V(1)>300 || V(2)>300 || V(3)>300 || V(4)>300 || V(5)>300 || V(6)>300 || V(7)>300 || V(8)>300 || V(9)>300
            k3.StopMotors;
            break
        end
    
end