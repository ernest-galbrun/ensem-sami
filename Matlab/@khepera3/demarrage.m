function r=demarrage(robot)
r=khepera3(robot);
r.SetConnectionMode(0)
a=r.Connect(robot);
if(a==1)
    disp('Echec de la connection.V�rifiez la connection puis r�essayez');
else disp('Connection r�ussie');
end
end
