function r=demarrage(id)
r=khepera3(id);a=1;
r.SetConnectionMode(0);
a=r.Connect(id)
if(a~=0)
    disp('Echec de la connection.Vérifiez la connection puis réessayez');
else disp('Connection réussie');
end
end
