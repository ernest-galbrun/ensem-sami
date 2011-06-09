function SetPID(k3,PID)
PID = PID * 30000;
calllib('khepera3clib', 'SetPID',k3.id,PID(1,1),PID(2,1),PID(3,1),PID(1,2),PID(2,2),PID(3,2));
end

