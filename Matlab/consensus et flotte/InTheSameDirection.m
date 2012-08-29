function Resp = InTheSameDirection(CurrentAngle,threshold)

%% Permet de comparer deux à deux les angles des differents robots

n = size(CurrentAngle,1);
answer=zeros(n,n);
Answer=zeros(n,1);

for i=1:n
            for j=1:n
                if(i~=j)
                    if(abs(CurrentAngle(i,1)-CurrentAngle(j,1)<=threshold))
                         answer(i,j)=1;
                    end
                end
            end
    if((sum(answer(i,:))==(n-1)))
        Answer(i)=1;
    end
Resp=all(Answer(:));
end

end