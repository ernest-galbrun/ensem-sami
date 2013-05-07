function [usage ref_trajectory actual_trajectory error t_total] = EventTrigger(myRobot, alwaysTrigger)%,traj)
%the shape function handle is of type : [x y theta v w] = f(t)

%% Module 0: Cleaning up

%clear all 
%clc
%myRobot.Connect(5,false,[0 0],pi/4);

%% Module 1: Initializing
%myRobot.SetConnectionMode(2)
%myRobot.Connect(3)
%pause(0.2);
goto(myRobot,0,0,30);
goto_theta(myRobot,0,30);

pause on
%close(gcf)

%% Module 2: Initial Parameters?

% Module 2.a: Total time and executions
pos = myRobot.GetXYPosition;
t_f = 40;
T = 0.02;
N = floor(t_f/T);

%[xr yr thetar vr wr d_vr d_wr] = myline(0:T:t_f,0,0,0,1);
%[xr yr thetar vr wr d_vr d_wr] = lemniscate_sym(0:T:t_f,0,0,1.2,0.1);
%xr = traj.x(1:length(xr));
%yr = traj.y(1:length(yr));
%thetar = traj.theta(1:length(thetar));
[xr yr thetar vr wr d_vr d_wr] = ellipse(0:T:t_f,0,0,0.8,0.5,0.2);

t=0;
ti = 1+round(t*N/t_f);

% Module 2.b: Control and Dynamic Equation related Variables

v_hat = 0;
w_hat = 0;

% a = 1.0; % m
% alpha = 0.1; % rad/s

c3 = 1;%0.1;%1;%0.7;%1;%0.7;
c4 = 0.01;%10;%0.3;%0.1;%1;%0.5;
c5 = 0.2;%1/gamma;%0.8;
gamma =1;%150;%2;
epsilon = 0.01;
sigma = 0.5;%0.5

% Module 2.d: Plotting Variables
t_total=0;
x_total = pos(1)/1000;
y_total = pos(2)/1000;

theta_hat = myRobot.GetOrientation() * ones(5,1);


theta_total = mean(theta_hat);

xr_total = xr(ti);
yr_total = yr(ti);
thetar_total = thetar(ti);

v_total = 0;
w_total = 0;
vr_total = vr(ti);
wr_total = wr(ti);

thetae_total = [];
xe_total = [];
ye_total = [];
V_total = [];
gammaetc = [];

verify_t = 0;
trigger_total = 1;
dotV_t = 0;
%% Module 3: Execution (without ETC)
%syms x y theta;
group = {'start'};
while t < t_f
    tic;
    
    ti = 2+floor(t*N/t_f);
    Position = myRobot.GetXYPosition(); % mm
    while (norm(Position - pos) > 100)
        Position = myRobot.GetXYPosition();
    end
%     if (norm(Position - pos) > 100)
%         %myRobot.Connect(3);
%         Position = myRobot.GetXYPosition();
%     end
    theta_hat = circshift(theta_hat,1);
    theta_hat(1) = myRobot.GetOrientation(); % rad
    theta = median(theta_hat);
    pos = Position;
    %
    x = Position(1,1)/1000; % m
    y = Position(1,2)/1000; % m
    % Control

    J = [ cos(theta) sin(theta) 0; -sin(theta)  cos(theta) 0; 0 0 1];

    x_aux = [(xr(ti) - x); (yr(ti) - y); wrapToPi(thetar(ti) - theta)];
    Xe = J*x_aux;

    xe = Xe(1);
    ye = Xe(2);
    thetae = Xe(3);

    % compute input according to Jiang's control law
    w = wr(ti) + 1*gamma*ye*vr(ti)*(sinc(thetae)) + c5*gamma*(thetae);
    gammaetc = [gammaetc  1*gamma*ye*vr(ti)*(sinc(thetae))];
    d_w = d_wr(ti)...
            + gamma * vr(ti) * sinc(thetae) * (vr(ti)*sin(thetae) - w * xe)...
            + gamma * ye * d_vr(ti) * sinc(thetae)...
            + gamma *  ye *  vr(ti) * (wr(ti) - w) * (thetae * cos(thetae) - sin(thetae)) / thetae^2 ...
            + c5 * gamma * (wr(ti) - w);
    v1 = vr(ti)*cos(thetae) - c3*d_w*ye + c3*w*(w*xe - vr(ti)*sin(thetae));
    xe_bar = xe - c3*w*(ye);    
    v = v1 + c4*xe_bar;


    ev = v_hat - v;
    ew = w_hat - w;   

    % Module 3.c: Triggering Condition
    rho = -gamma*xe*vr(ti)*sinc(thetae) - gamma*ye*vr(ti)*(thetae*cos(thetae)-sin(thetae))/thetae^2 ...
          - c5*gamma;
    SIGMA = c3*w^2*ye^2 + c4*xe_bar^2 + c5*thetae^2;
    LAMBDA = xe_bar * (ew*ye - ev - c3*ew*rho*ye + c3*w*ew*xe)...
             - ye*ew*xe - thetae*ew/gamma;
    V = xe_bar*xe_bar/2 + ye*ye/2 + thetae*thetae/2/gamma; 
    V_total = [V_total V];


    
    recv_elapse = toc;
%     
%  
%     SIGMA_ = eval(SIGMA);
%     LAMBDA_ = eval(LAMBDA);
    
    if alwaysTrigger || (-SIGMA+LAMBDA >= -sigma*SIGMA && V >= epsilon*epsilon);
        % Updating Control
        
     
        VMAX = 250;
        WMAX = 2*pi;
        v_real = v*1000;
        w_real = w;
        
        
%         v_real = vr(ti)*1000;
%         w_real = wr(ti);
        v_real = min(v_real,VMAX);
        v_real = max(v_real,-1*VMAX);
        w_real = min(w_real,WMAX);
        w_real = max(w_real,-1*WMAX);
        
        myRobot.SetVelocity(v_real, w_real);
        
        send_elapse = toc;
        
        v_hat = v;
        w_hat = w;
        
        trigger = 1;
        
        group{length(group)+1} = 'trigger';
        % pause(T);
        
    else
        trigger = 0;
        if -SIGMA+LAMBDA >= -sigma*SIGMA
            group{length(group)+1} = 'V small';
        elseif V >= epsilon*epsilon
            group{length(group)+1} = 'trig condition not met';
        else
            group{length(group)+1} = 'V small and trig condition not met';
        end
    end
    
    % Time passing
    while toc<T
    end    
    t = t+toc;
    
    
    t_total = [t_total ; t];
    
    x_total = [x_total ; x];
    y_total = [y_total ; y];
    theta_total = [theta_total ; theta];
    
    
    xr_total = [xr_total ; xr(ti)];
    yr_total = [yr_total ; yr(ti)];
    thetar_total = [thetar_total ; thetar(ti)];
    xe_total = [xe_total xe_bar];
    ye_total = [ye_total ye];
    thetae_total = [thetae_total thetae];
    
    v_total = [v_total ; v_hat];
    w_total = [w_total ; w_hat];
    
    vr_total = [vr_total ; vr(ti)];
    wr_total = [wr_total ; wr(ti)];
    
    trigger_total = [trigger_total; trigger];
    
end

myRobot.SetVelocity(0, 0);

%myRobot.Disconnect();

%% Module 4: Plotting
% 
f1 = figure(1);
axis square;
%plot(xr_total,yr_total,'--r')
hold on
plot(x_total,y_total,'b')

% f1 = figure(1);
 plot(xr_total,yr_total,'--r')
%hold on
% %axis([-0.8 0.8 -0.5 0.5])
%plot(x_total,y_total,'b')
colormap jet
gscatter(x_total,y_total,group')
xlabel('x (m)')
ylabel('y (m)')
title('robot trajectory and reference trajectory')
legend('ref','robot')

% f2 = figure(2);
% stairs(t_total,v_total,'--b')
% hold on
% stairs(t_total,w_total,'k')
% stairs(t_total,wr_total,'r')
% stairs(t_total,vr_total,'r')
% xlabel('Time (s)')
% ylabel('Value')
% title('Plot of v (linear velocity) and w (angular velocity)')
% legend('v','w','vr','wr')
% 
% figure(3)
% plot(t_total, theta_total,'--r')
% hold on
% plot(t_total,thetar_total,'k')
% xlabel('Time (s)')
% ylabel('Value')
% title('Plot of \Theta_r and \Theta')
% legend('\Theta_e')%,'\Theta')
% 
% f4 = figure(4);
% subplot(2,1,1), plot(t_total,trigger_total,'b.');
% axis([0 t_f 0 2])
% xlabel('Time (s)')
% ylabel('Value')
% title('Plot of Trigger vs Time')
% legend('1 = Trigger, 0 = No Trigger')
% subplot(2,1,2), plot(t_total,dotV_t,'k','Linewidth',1.5);
% hold on
% plot(t_total,verify_t,'r--','Linewidth',1.5);
% xlabel('Time (s)')
% ylabel('Value')
% title('Plot of $\dot{V}$ and $\Sigma$','interpreter', 'latex');
% h2 = legend('$\dot{V}$','$\Sigma$');
% 
% %set(h1, 'interpreter', 'latex')
% set(h2, 'interpreter', 'latex')
% 
% % Function used to compare the number of transmissions between
% % implementations

usage = sum(trigger_total)/length(trigger_total);

ref_trajectory = struct('x',xr_total,'y',yr_total,'theta', thetar_total,...
                        'v', vr_total, 'w', wr_total);
actual_trajectory = struct('x',x_total,'y',y_total,'theta', theta_total,...
                        'v', v_total, 'w', w_total);
error = [xe_total;ye_total;thetae_total;V_total];
end


% function [x y theta] = lemni(t,xc,yc,alpha)   
%     x = xc + a*sin(alpha*t)/(1+(sin(alpha*t))^2);
%     y = yc + a*sin(alpha*t)*cos(alpha*t)/(1+(sin(alpha*t))^2); 
%     theta = -atan(1/(a*alpha*cos(alpha*t)/(sin(alpha*t)^2 + 1) ...
%         - 2*a*alpha*cos(alpha*t)*sin(alpha*t)^2/(sin(alpha*t)^2 + 1)^2)*(a*alpha*sin(alpha*t)^2/(sin(alpha*t)^2 + 1) ...
%         - a*alpha*cos(alpha*t)^2/(sin(alpha*t)^2 + 1)...
%         + 2*a*alpha*cos(alpha*t)^2*sin(alpha*t)^2/(sin(alpha*t)^2 + 1)^2));    
% end
