function StartFollowLine(k3,agressivity,velocity)

calllib('khepera3clib', 'StartMotors',k3.id);
calllib('khepera3clib','FollowLine',k3.id,true,agressivity,velocity);

end