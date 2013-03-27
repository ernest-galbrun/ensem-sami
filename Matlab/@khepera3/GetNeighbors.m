function neighbors = GetNeighbors(k3)
id = libpointer('int32PtrPtr');
x = libpointer('doublePtrPtr');
y = libpointer('doublePtrPtr');
nNeighbors = libpointer('int32Ptr',0);
error = calllib('khepera3clib','GetNeighbors',k3.id,nNeighbors,id,x,y);
if error
    ME = MException('GetPosition:CommunicationError', ...
         'The connection with the robot has failed. Check the network and try to reconnect');
    throw(ME);
end
n = get (nNeighbors,'value');
neighbors = zeros(3,n);
if n~=0
    id = get(id,'value');
    setdatatype(id,'int32Ptr',n)
    neighbors(1,:) = get(id,'value');
    x = get(x,'value');
    setdatatype(x,'doublePtr',n)
    neighbors(2,:) = get(x,'value');
    y = get(y,'value');
    setdatatype(y,'doublePtr',n)
    neighbors(3,:) = get(y,'value');
end

