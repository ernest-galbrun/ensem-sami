function r=demarrage(id)
r=khepera3(id);a=1;
r.SetConnectionMode(0);
a=r.Connect(id)
if(a~=0)
    disp('Echec de la connection.V�rifiez la connection puis r�essayez');
else disp('Connection r�ussie');
end
end
