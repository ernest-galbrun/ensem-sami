function AddKhepera(KheperaFleet,Id,Virtual)
temp = khepera3();
temp.Connect(Id,'193.49.136.176',Virtual);


KheperaFleet.KheperaArray = [KheperaFleet.KheperaArray;temp];

% Update of the number of khepera object in the Fleet
KheperaFleet.NumberOfKhepera = size(KheperaFleet.KheperaArray,1);

end