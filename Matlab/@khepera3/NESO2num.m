function O = NESO2num()
ok=0;
while(ok==0)
    ok=1;
    ptcard=input('Orientation(N,E,S ou O cf. schéma circuit : ','s');
    switch ptcard
        case{'N','n'}
            O=1i;
        case{'E','e'}
            O=1;
        case{'S','s'}
            O=-1i;
        case{'O','o'}
            O=-1;
        otherwise
            disp('Instruction erronée');
            ok=0;
    end
end
end



