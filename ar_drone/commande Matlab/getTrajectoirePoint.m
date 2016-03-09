function [ Xref, Stop ] = getTrajectoirePoint( XposInit,typeTrajectoire, time,zRef,tVol )
%getTrajectoirePoint fonction qui renvoi le point de référence selon la trajectoire choisie 
%   Les trajectoires partent toutes de la position initiale du drone après décollage à l'altitude zref

%XposInit(1) : x
%XposInit(2) : y
%XposInit(3) : z
%XposInit(4) : yaw
%XposInit(5) : vitesse forward
%XposInit(6) : vitesse laterale

%Xref(1) : xref
%Xref(2) : yref
%Xref(3) : zref


Stop=0;

 switch typeTrajectoire
    
        %droite
      case 0 
%           if time<floor(tVol/4)
%               xRef=XposInit(1)+100*time;
%               yRef=XposInit(2); 
%           elseif time<floor(tVol/2)
%               xRef=XposInit(1);
%               yRef=XposInit(2)+100*(time-tVol/4);
%           elseif time<floor(3*tVol/4)
%               xRef=XposInit(1)-100*(time-tVol/2);
%               yRef=XposInit(2);
%           else
%               xRef=XposInit(1);
%               yRef=XposInit(2)-100*(time-3*tVol/4);
%               Stop=1;
%           end


%             xRef=XposInit(1)+10*time;
%             yRef=XposInit(2);
         
              xRef=500;
              yRef=500;          
          
        % cercle
      case 1  
          RAYON=400;
          xRef=XposInit(1) - RAYON + RAYON*cos(time);
          yRef=XposInit(2) + RAYON*sin(time);
%             xRef= RAYON*cos(abs(time))- RAYON;
%             yRef= RAYON*sin(abs(time));
         
        % ellipse
      case 2  
          DEMI_GRAND_AXE=400;
          DEMI_PETIT_AXE=200;
          xRef=XposInit(1) - DEMI_GRAND_AXE + DEMI_GRAND_AXE*cos(abs(time));
          yRef=XposInit(2) + DEMI_PETIT_AXE*sin(abs(time));
       
          % Lemniscate de Bernouilli
      case 3  
          if(time<tVol/2)% partie de la lemniscate ou xRef<0 et yRef<0 (aprés inv)
              xRef=XposInit(1) + 400*(2*time)/(1+time^4);
              yRef=XposInit(2) + 400*(2*time^3)/(1+time^4);
          else
              time=-(tVol/2-time); % partie de la lemniscate ou xRef>0 et yRef>0 (aprés inv)
              xRef=XposInit(1) + 400*(2*time)/(1+time^4);
              yRef=XposInit(2) + 400*(2*time^3)/(1+time^4);
          end %inv 
%               xRef=-xRef;
%               yRef=-yRef;
              
       otherwise
        disp('erreur typeTrajectoire');
        Stop=1;
 end
                
                
        Xref=[xRef yRef zRef];
        
   %Condition d'arrêt (une fois la trajectoire cyclique bouclée)
   %lorsque le drone revient à sa postion de départ avec une tolérance sur
   %la position finale, on fait atterir le drone via Stop
%    TOLERANCE_ECART_POSITION_INITIALE_FINALE=50; %en mm
%    if abs(XposInit(1)-xRef)<TOLERANCE_ECART_POSITION_INITIALE_FINALE && abs(XposInit(2)-yRef)<TOLERANCE_ECART_POSITION_INITIALE_FINALE && abs(XposInit(3)-zRef)<TOLERANCE_ECART_POSITION_INITIALE_FINALE && abs(time-toc)>10
%         Stop=1;
%    end
end

