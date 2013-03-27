%Get orientation
function orientation = GetOrientation(k3)
%%explication
    x = libpointer('doublePtr',0);
    error = calllib('khepera3clib', 'GetOrientation',k3.id,x);
    if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
    end
    orientation = get(x,'value');
  %  orientation = orientation -3*pi/180;
end

