%ellipse
load results/result44.mat
close all
plot(ref.x(1:1600),ref.y(1:1600),'--black','LineWidth',2)
pos0 = [traj.x(1) traj.y(1)];
axis equal
hold on
plot(traj.x(1:50:end),traj.y(1:50:end),'o-black','MarkerSize',6,...
    'MarkerFaceColor',[0.75 0.75 .75])
load results/result43.mat
plot(traj.x,traj.y,'x--blue','MarkerSize',10,...
    'MarkerFaceColor',[0.75 0.75 .75],...
    'LineWidth',1.5)
plot([0 traj.x(1) pos0(1)] ,[-0.8 traj.y(1) pos0(2)],'*r','markersize',8,'linewidth',1)
xlabel('x(mm)')
ylabel('y(mm)')
legend('Reference trajectory','Event triggered','Time triggered','Starting positions','Location','NorthEast')
legend('boxoff')
axis([-0.6 1.4 -0.9 0.9])

% 
% %lemniscate
% load results/result40.mat
% close all
% plot(ref.x(1:3130),ref.y(1:3130),'--black','linewidth',2)
% axis equal
% hold on
% plot(traj.x(1:50:end),traj.y(1:50:end),'o-black','markersize',6,...
%     'markerfacecolor',[0.75 0.75 .75])
% pos0 = [traj.x(1) traj.y(1)];
% load results/result42.mat
% plot(traj.x,traj.y,'x--blue','markersize',8,...
%     'markerfacecolor',[0.75 0.75 .75],...
%     'linewidth',1.5)
% plot([0 traj.x(1) pos0(1)] ,[0 traj.y(1) pos0(2)],'*r','markersize',8,'linewidth',1)
% xlabel('x(mm)')
% ylabel('y(mm)')
% legend('Reference trajectory','Event triggered','Time triggered','Starting positions','location','northwest')
% legend('boxoff')
% axis([-1. 0.65 -0.6 0.9])