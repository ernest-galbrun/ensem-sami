function t=lancement2(r)
n=numel(r);D(n,2)=0;A(n,2)=0;O(n)=0;
disp('départ');
for j=1:n
    robot=input(['Numéro du robot n°', num2str(j),' (respecter ordre du tableau argument)']);
    X=input('Position de départ : ');D(j,1)=X(1);D(j,2)=X(2);
    X=input('Destination : ');A(j,1)=X(1);A(j,2)=X(2);
    O(j)=NESO2num();
    t{j,1}=r(j);
    t{j,2}=1;
    t{j,3}=5000;
    [u X Y V]=move8(r(1),O(j),D(j,:),A(j,:));u=[u;0];disp(u);
    p(length(u))=0;p=p';
    
    % récupération des parcours des robots S1 {V1 V2 .... Vn}
    
    S1{1,j}=V ;
    %application 
   
     t{j,4}=u;

end
  [P t]=CompareConflit(t{1,1},S1,t);
  
for i=1:n
    disp('robot : ');disp(i)
    disp(t{i,4})
end
disp(P)
r.Deplacement2(t,S1,P);
