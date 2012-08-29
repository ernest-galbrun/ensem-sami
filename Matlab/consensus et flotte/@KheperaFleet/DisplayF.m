function DisplayF(KheperaFleet,varargin)
optargin = size(varargin,2);
[X Y] = KheperaFleet.GetPositionF;
Phi = KheperaFleet.GetOrientationF;

u = 20*cosd(Phi*2*360/(2*pi))+X;
v = 20*sind(Phi*2*360/(2*pi))+Y;
plot(X(:,1),Y(:,1),'ro');
hold on
quiver(X(:,1),Y(:,1),u(:,1)-X(:,1),v(:,1)-Y(:,1),0);
hold on
ht = text(X(:,1)+20*ones(size(X,1),1),Y(:,1)+20*ones(size(Y,1),1),num2str([1:1:size(X,1)]'));
set(ht,'HorizontalAlignment','right')
plot(ht)
hold on

if optargin>0
    if(strcmp(varargin{1},'Network'))
        for i=1:KheperaFleet.NumberOfKhepera
            for j =1:KheperaFleet.NumberOfKhepera
                if(KheperaFleet.Network(i,j) ==1)
                    plot([X(i,1),X(j,1)],[Y(i,1),Y(j,1)],'g');
                    hold on;
                end
            end
        end
    else
        error('This option in not valid for DisplayF method');
    end
end
hold off;
end