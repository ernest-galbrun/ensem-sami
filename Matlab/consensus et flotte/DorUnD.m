function Answer = DorUnD(CurrentAngle,FinalAngle)

for i =1:size(CurrentAngle);
    if(CurrentAngle(i)>FinalAngle(i))
        if(CurrentAngle(i)-FinalAngle(i)>pi)
            Answer(i,1) = 1;
        else
            Answer(i,1) = -1;
        end
    else
        if(FinalAngle(i)-CurrentAngle(i)>pi)
            Answer(i,1) = -1;
        else
            Answer(i,1) = 1;
        end
    end 
end

end