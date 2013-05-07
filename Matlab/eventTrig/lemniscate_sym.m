function [x y theta v w d_v d_w] = lemniscate_sym(T,xc,yc,a,alpha)   
% xc, yx: coordinates of the center
% a: total length of the lemniscate
% alpha: speed of the lemniscate (in "rad"/unit of time): the lemniscate is
% completed when t = 2*pi/alpha
    
    syms t;
    syms t2;
    t = t2;%+sin(t2);
    x = xc + a*sin(alpha*t)/(1+(sin(alpha*t))^2);
    y = yc + a*sin(alpha*t)*cos(alpha*t)/(1+(sin(alpha*t))^2); 
    % theta = atan2(y'/x')
    theta = 2* atan(diff(y)./(sqrt(diff(x).^2+diff(y).^2)+diff(x)));     
    v = sqrt(diff(x).^2+diff(y).^2);
    w = diff(theta);
    d_v = diff(v);
    d_w = diff(w);
    t2=T;
    x = eval(x);
    y = eval(y);
    theta = eval(theta);
    v = eval(v);
    w = eval(w);
    d_v = eval(d_v);
    d_w = eval(d_w);
end
