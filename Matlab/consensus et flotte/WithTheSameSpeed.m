function Answer = WithTheSameSpeed(Vlin,threshold)

%% Permet de comparer deux à deux les vitesses des robots

n = size(Vlin,1);
answer=zeros(n,n);
Answer=zeros(n,1);
for i=1:n
            for j=1:n
                if(i~=j)
                    if(Vlin(i,1)-Vlin(j,1)<=threshold)
                         answer(i,j)=1;
                    end
                end
            end
    if((sum(answer(i,:))==(n-1)))
        Answer(i)=1;
    end

end

end