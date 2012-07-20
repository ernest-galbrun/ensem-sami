function goto(r,dest,time)
tic;
t=toc;
K1 = 1;
K2 = 0.2;
while(t<time)
    d = dest - r.GetXYPosition;
    dist = norm(d)
    diff_angle = atan2(d(2),d(1)) - r.GetOrientation
    v = K1 * dist;
    v_theta = K2 * diff_angle
    v = v*cos(diff_angle)
    r.SetVelocity(v,v_theta);
    t = toc;
end
r.SetVelocity(0,0)