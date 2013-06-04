function goto(r,x,y,t)
tic
dist=inf;
while(toc<t && dist>70)
    theta=r.GetOrientation();
    pos = r.GetXYPosition();
    Ex=x-pos(1);
    Ey=y-pos(2);
    dist=sqrt(Ex^2+Ey^2);

    thetap=atan2(Ey,Ex);
    if thetap<0
        thetap=thetap+2*pi;
    end;
    Etheta=thetap-theta;
    if(Etheta>pi)
        Etheta = Etheta-2*pi;
    elseif(Etheta<-pi)
            Etheta=Etheta+2*pi;
    end

    V=0.5*dist*cos(Etheta);
    Omega=Etheta;
    r.SetVelocity(V,Omega);
    pause(0.05);
end
r.SetVelocity(0,0);