function goto_theta(r,thetaR,t)
Etheta = inf;
tic
while(toc<t && abs(Etheta)> (5* pi / 180))
    theta=r.GetOrientation();
    Etheta=thetaR-theta;
    if(Etheta>pi)
        Etheta = Etheta-2*pi;
    elseif(Etheta<-pi)
            Etheta=Etheta+2*pi;
    end

    Omega=Etheta;
    r.SetVelocity(0,Omega);
    pause(0.05);
end
r.SetVelocity(0,0);