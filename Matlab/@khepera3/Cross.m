function Cross(k3,direction,agressivity,velocity)

%Cette fonction appelle la fonction Cross qui est intégré dans le robot.
%Elle permet de franchir une intersection de la manière suivante : 
% 1 = Droite | 0 = Tout droit | 2 = Gauche | 3 = Demi tour (pour direction)



k3.StartMotors
error = calllib('khepera3clib','Cross',k3.id,direction,agressivity,velocity);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end

end