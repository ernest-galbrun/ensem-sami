function Phi = GetOrientationF(KheperaFleet)
Phi = zeros(KheperaFleet.NumberOfKhepera,1);
for i = 1:KheperaFleet.NumberOfKhepera
    Phi(i,1) = KheperaFleet.KheperaArray(i,1).GetOrientation;
end
Phi = mod(Phi,2*pi);

end