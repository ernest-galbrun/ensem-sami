function SetVelocityF(KheperaFleet,LinearVelocity,AngularVelocity)
for i=1:KheperaFleet.NumberOfKhepera
    KheperaFleet.KheperaArray(i,1).SetVelocity(LinearVelocity(i),AngularVelocity(i));
end