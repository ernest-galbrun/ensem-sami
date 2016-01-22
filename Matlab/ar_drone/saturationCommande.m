function valeurOut=saturationCommande(valeurIn,borneInf,borneSup)
%Fonction permettant de saturer une valeur
%entre borneInf et borneSup

    valeurOut=zeros(length(valeurIn),1);

    for i=1:length(valeurIn)
        if valeurIn(i)>borneSup
            valeurOut(i)=borneSup;
        elseif valeurIn(i)<borneInf
            valeurOut(i)=borneInf;
        else
            valeurOut(i)=valeurIn(i);
        end
    end
end