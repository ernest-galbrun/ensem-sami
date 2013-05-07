function [x y theta v w d_v d_w] = ellipse(T,xc,yc,a,b,alpha)   
% xc, yx: coordinates of the center
% a: vertical semi-axis
% b: horizontal semi-axis
% alpha: speed of the lemniscate (in "rad"/unit of time): the ellipse is
% completed when t = 2*pi/alpha
    syms t;  
    y = a*sin(alpha*t);
    x = b*cos(alpha*t);
    theta = 2*atan(y/(sqrt(x*x+y*y)+x));
    w = diff(theta);    
    x = b*sin(alpha*t)+xc;
    y = -a*cos(alpha*t)+yc;
    v = sqrt(diff(x).^2+diff(y).^2);
    d_v = diff(v);
    d_w = diff(w);
    t=T;
    x = eval(x);
    y = eval(y);
    theta = eval(theta);
    v = eval(v);
    w = eval(w);
    d_v = eval(d_v);
    d_w = eval(d_w);
end
