function r=demarrage(robot)
r=khepera3(robot);
r.SetConnectionMode(0)
a=r.Connect(robot);
if(a==1)
    disp('Echec de la connection.Vérifiez la connection puis réessayez');
else disp('Connection réussie');
end
end
