function lancement(r)
n=numel(r);D(n,2)=0;A(n,2)=0;O(n)=0;
    for j=1:n
        robot=input(['Num�ro du robot n�', num2str(j),' (respecter ordre du tableau argument)']);
        X=input('Position de d�part : ');D(j,1)=X(1);D(j,2)=X(2);
        X=input('Destination : ');A(j,1)=X(1);A(j,2)=X(2);
        O(j)=NESO2num();
        t{j,1}=r(j);
        t{j,2}=1;
        t{j,3}=5000;
        [u X Y V]=move8(O(j),D(j,:),A(j,:));u=[u;0];%disp(u);
        p(length(u))=0;p=p';q=p;
        ok=0;
        while(ok==0)
            ok=1;
            prio=input('le robot doit il c�der la priorit�? (O/N) : ','s');
            if(prio~='O' && prio~='o' && prio~='N' &&prio~='n')
                disp('Instruction erron�e'); disp(' ');
                ok=0;
            end
        end
        if(prio=='O' || prio=='o')
            disp(V);ok=0;
            while(ok==0)
                m=input('le combienti�me noeud parmi la liste pr�c�dente est source de conflit ? ');
                p(m)=input('num�ro du robot prioritaire');
                q(m)=input('patch associ� :');
                ok=1;ok2=0;
                while(ok2==0)
                    ok2=1;
                    prio=input('Autre conflit (priorit� � c�der) ? ','s');
                    if(prio~='O' && prio~='o' && prio~='N' &&prio~='n')
                        disp('Instruction erron�e'); disp(' ');
                        ok2=0;
                    end
                    if(prio=='O' || prio=='o')
                        disp(V);ok=0;
                    end
                end
            end
        end
        t{j,4}=[u,p,q];
    end
    r.Deplacement2(t);
    
      