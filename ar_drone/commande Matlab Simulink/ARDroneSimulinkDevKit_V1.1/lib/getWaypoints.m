function [ waypoint ] = getWaypoints(  )
%GETWAYPOINTS Generates a list of waypoints for the ARDrone
%   Each waypoint is a column vector that contains the desired position of the
%   drone, desired heading angle, and waiting time. The list of waypoints
%   is created combining the column vectors. 

% Number of waypoints. Edit this value as desired. 
nPoints = 50;

waypointsListARDrone = zeros(5,nPoints);

% Edit the following entries for k =1,2,...,nPoints
% waypointsListARDrone(:,k) = [ Xe (m), Ye (m), h (m) , waiting time (sec)


% waypointsListARDrone(:,1) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,2) = [0.2;0;1;0; 0.1] ; 
% waypointsListARDrone(:,3) = [0.2;0.2;1;0; 0.1] ; 
% waypointsListARDrone(:,4) = [0;0.2;1;0; 2] ; 
% waypointsListARDrone(:,5) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,6) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,7) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,8) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,9) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,10) = [0;0;1;0; 5] ; 
% waypointsListARDrone(:,11) = [0;0;1;0; 5] ; 


    

%%
typeTrajectoire=1; %(0=point / 1=cercle / 2=ellipse /3 lemniscate de Bernouilli)
waitingTime=1; %(en s)
for k=1:nPoints

    switch typeTrajectoire

            %droite
          case 0 
                waypointsListARDrone(:,k) = [(k-1)/100;0;1;0; 5] ; 
            % cercle
          case 1  
              RAYON=0.5; %(en m)
              waypointsListARDrone(:,k) = [-RAYON + RAYON*cos(k-1);RAYON*sin(k-1);1;0; waitingTime] ; 
            % ellipse
          case 2  
              DEMI_GRAND_AXE=0.4;
              DEMI_PETIT_AXE=0.2;
              waypointsListARDrone(:,k) = [-DEMI_GRAND_AXE + DEMI_GRAND_AXE*cos(k-1);DEMI_PETIT_AXE*sin(k-1);1;0; waitingTime] ; 

              % Lemniscate de Bernouilli
          case 3  
              DEMI_GRAND_AXE=0.4;
              if(k<nPoints/2)% partie de la lemniscate ou xRef<0 et yRef<0 (aprés inv)
                  waypointsListARDrone(:,k) = [DEMI_GRAND_AXE*(2*(k-1))/(1+(k-1)^4);DEMI_GRAND_AXE*(2*(k-1)^3)/(1+(k-1)^4);1;0; waitingTime] ; 
                  
              else
                  k1=(nPoints/2-k); % partie de la lemniscate ou xRef>0 et yRef>0 (aprés inv)
                  waypointsListARDrone(:,k) = [DEMI_GRAND_AXE*(2*k1)/(1+k1^4);DEMI_GRAND_AXE*(2*k1^3)/(1+k1^4);1;0; waitingTime] ; 
              end  
    

        otherwise
               if k==1
            disp('erreur typeTrajectoire');
               end
     end

end

waypoint = waypointsListARDrone ; 

end

