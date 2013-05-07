function [x y theta v w d_v d_w] = myline(T,x0,y0,alpha,length_)   
% xc, yx: coordinates of the center
% a: total length of the lemniscate
% alpha: speed of the lemniscate (in "rad"/unit of time): the lemniscate is
% completed when t = 2*pi/alpha
    syms t;
    x = x0 + cos(alpha)*t*length_/T(length(T));
    y = y0 + sin(alpha)*t*length_/T(length(T));
    % theta = atan2(y'/x')
    theta = alpha*t^0;     
    v = sqrt(diff(x).^2+diff(y).^2);
    w = diff(theta);
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
    x = expand(x);
    y = expand(y);
    theta = expand(theta);
    v = expand(v);
    w = expand(w);
    d_v = expand(d_v);
    d_w = expand(d_w);
    

    function y = expand(x)
        if length(x)==1
            y = ones(1,length(T))*x;
        else
            y = x;
        end
    end
end