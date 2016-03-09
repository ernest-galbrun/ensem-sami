function Deplacement3(r,O,D,A)
t{1,1}=r;
t{1,2}=1;
t{1,3}=5000;
u=move7b(O,D,A);
v(numel(u))=0;
t{1,4}=[u,v',v'];disp(t{1,4});%type(t{1,1});type(t{1,2});type(t{1,3});
r.Deplacement2(t);
end
