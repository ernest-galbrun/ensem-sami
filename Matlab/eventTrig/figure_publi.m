
%lemniscate :
% eps = [0.01 0.02 0.05 0.1 0.2 0.5];
% err_tt = [0.016 0.018 0.0509 0.1047 0.2803 1.2411];
% err_et = [0.0159 0.026 0.0542 0.1064 0.1947 0.6371];
% base_error = mean([0.0121 0.0118 0.0127 0.0129]);

%ellipse :
eps = [0.01 0.02 0.05 0.1 0.2 0.5];
err_tt = [0.012 0.0099 0.0522 1.4396 0.3549 0.4167];
err_et = [0.0122 0.0129 0.048 0.0731 0.1564 0.5256];
base_error = 0.0081;


close all;
hold on
line([-1000 1000],[base_error base_error],'Marker','none',...
    'LineWidth',2,'LineStyle' , '--','color','black')
semilogx(log(eps),err_et,'LineWidth',2,'color','blue','Marker',...
    'x','MarkerSize',12,'MarkerFaceColor' , [.75 .75 1]);
semilogx(log(eps),err_tt,'LineWidth',2,'color','red',...
    'Marker','o','MarkerSize',8)
legend('Base Error','Event triggered','Time triggered','Location','NorthWest')
legend('boxoff')
set(gca,'XTick',eps)
set(gca,'XTick',log(eps),'XTickLabel',eps,'XMinorTick','off')

set(gca,'YGrid' , 'on')
xlabel('Epsilon')
ylabel('Error')

dx = log(eps(end)) - log(eps(1));
dx = dx*0.1;
axis([log(eps(1))-dx log(eps(end))+dx 0 max([err_tt err_et])*1.1])
