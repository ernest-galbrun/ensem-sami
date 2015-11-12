function [  ] = plotVol( tps, drone, hover, cmd )
%plotVol Affiche les données de vol et les commandes recueillies
%   Données du drone, des commandes et de la référence

figure('Name','Données Drone');
    subplot(3,2,[1 3 5]); hold on;
        plot3(drone(:,1),drone(:,2),drone(:,3),'b.');
%         plot3(drone(:,1),drone(:,2),drone(:,3),'-');
        title('Trajectoire 3D'); hold off; grid on; axis square;
        xlabel('x');ylabel('y');zlabel('z');
    subplot(3,2,2)
        plot(tps,drone(:,4))
        title('Yaw');xlabel('t');ylabel('yaw (rad)'); grid on;
    subplot(3,2,4);
        plot(tps,drone(:,5))
        title('Pitch');xlabel('t');ylabel('pitch (rad)'); grid on;
    subplot(3,2,6);
        plot(tps,drone(:,6))
        title('Roll');xlabel('t');ylabel('roll (rad)'); grid on;

figure('Name', 'Commandes et effets');
    subplot(421)
        plot(tps,cmd(:,1));
        title('Commande Roll');
        ylabel('CmdPitch');xlabel('t');grid on;
    subplot(422); hold on;
        plot(tps,hover(:,1));
        plot(tps,drone(:,1),'r'); hold off;
        title('Ecart position/consigne sur x');
        ylabel('x (mm)');xlabel('t');grid on;
    subplot(423)
        plot(tps,cmd(:,2));
        title('Commande Pitch');
        ylabel('CmdRoll');xlabel('t');grid on;
    subplot(424); hold on;
        plot(tps,hover(:,2));
        plot(tps,drone(:,2),'r'); hold off;
        title('Ecart position/consigne sur y');
        ylabel('y (mm)');xlabel('t');grid on;
    subplot(425)
        plot(tps,cmd(:,3));
        title('Commande Vitesse Ascensionnelle');
        ylabel('CmdZDot');xlabel('t');grid on;
    subplot(426); hold on;
        plot(tps,hover(:,3));
        plot(tps,drone(:,3),'r'); hold off;
        title('Ecart position/consigne sur z');
        ylabel('z (mm)');xlabel('t');grid on;
    subplot(427)
        plot(tps,cmd(:,4));
        title('Commande Vitesse Yaw');
        ylabel('CmdYawDot');xlabel('t');grid on;
    subplot(428); hold on;
        plot(tps,zeros(length(tps),4));
        plot(tps,drone(:,4),'r'); hold off;
        title('Ecart position/consigne sur le yaw');
        ylabel('yaw (rad)');xlabel('t');grid on;

end

