function decollage(port)
%Gestion du sequence number
global sequenceNumber;
sequenceNumber=sequenceNumber+1;

%Commande de decollage
fwrite(port,sprintf('AT*REF=%d,290718208\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*REF=%d,290718208\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*REF=%d,290718208\r',sequenceNumber));
sequenceNumber=sequenceNumber+1;
fwrite(port,sprintf('AT*REF=%d,290718208\r',sequenceNumber));
%On lui laisse le temps de se stabiliser
for i=sequenceNumber:sequenceNumber+100
   sequenceNumber=sequenceNumber+1;
   fwrite(port,sprintf('AT*COMWDG=%d\r',sequenceNumber)); 
   pause(0.05);
end
end