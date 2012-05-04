function SetVelocity(k3,linearVelocity, angularVelocity)
%linearvelocity in cm/s
%angularvelocity in rad/s
calllib('khepera3clib', 'SetSpeed',k3.id,linearVelocity,angularVelocity);
end

