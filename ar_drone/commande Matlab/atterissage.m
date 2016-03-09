function atterissage(port)
%Gestion du sequence number
global sequenceNumber;
sequenceNumber=sequenceNumber+1;

%On demande au drone d'atterir
for i=sequenceNumber:sequenceNumber+100
    fwrite(port,sprintf('AT*REF=%d,290717696\r',sequenceNumber));
    sequenceNumber=sequenceNumber+1;
end
end