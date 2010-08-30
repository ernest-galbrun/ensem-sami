function SetMode(k3,modeLeft,modeRight)
    calllib('khepera3clib', 'SetMode',k3.id,modeLeft-1, modeRight-1);
end

