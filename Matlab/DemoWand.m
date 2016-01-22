function DemoWand(Robot1, t_final)

tid = tic;
%t/0.02;
while(toc(tid)<t_final)
   % tic
    i;%
    % Obtention des données
    positionR=Robot1.GetXYPosition();
  %  while positionR == [0 0]
 %   	positionR=Robot1.GetXYPosition();
 %   end
    positionW = Robot1.GetWandPosition;
   % positionW = [0 0];
    % récupère la position pointée par la tige
    Xp = positionW(1);
    Yp = positionW(2);
    goto(Robot1,Xp,Yp,0.1);
    %t_elapsed = toc;
end;
Robot1.SetVelocity(0,0)







