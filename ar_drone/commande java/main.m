% /!\ 
% If the path of this folder is changed, the program may not work.
% The file C:\Users\Khepera\Documents\MATLAB\javaclasspath.txt must
% be edited to add the new path in the static javaclasspath,
% including the paths for the jar files which are necessary.

% About ThreadNdt :
% If the ThreadNdt is defined as global variable, 
% there will be navdata of all flights on the graph,
% while the figure is not destroyed. On the contrary,
% if it's defined as local variable in takeoff, there will
% be only the navdata of the last flight.

function main
    figNdt = figure('units', 'pixels', ...
            'position', [500 250 700 700], ...
            'name', 'guiNavData',...
            'DeleteFcn',@leave);
    
    uicontrol('style', 'pushbutton', ...
        'units', 'pixels', ...
        'position',[75 200 150 150], ...
        'string','Start',...
        'tag','takeoff_button',...
        'enable','on',...
        'FontSize',18,...
        'callback', @takeoff);
        
    uicontrol('style','text',...
        'string','Battery : ',...
        'units','pixels',...
        'position',[50 100 160 44],...
        'HorizontalAlignment','left',...
        'FontSize',12,...
        'tag','bat_text');
    
    uicontrol('style','text',...
        'string','Theta : ',...
        'units','pixels',...
        'position',[10 450 90 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','tta_text');
    
    uicontrol('style','text',...
        'string','Phi : ',...
        'units','pixels',...
        'position',[110 450 90 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','phi_text');
    
    uicontrol('style','text',...
        'string','Psi : ',...
        'units','pixels',...
        'position',[210 450 90 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','psi_text');
    
    uicontrol('style','text',...
        'string','Altitude : ',...
        'units','pixels',...
        'position',[450 450 100 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','alt_text');
    
    uicontrol('style','text',...
        'string','Vx : ',...
        'units','pixels',...
        'position',[340 200 100 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','vx_text');
    
    uicontrol('style','text',...
        'string','Vy : ',...
        'units','pixels',...
        'position',[460 200 100 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','vy_text');
    
    uicontrol('style','text',...
        'string','Vz : ',...
        'units','pixels',...
        'position',[580 200 100 18],...
        'HorizontalAlignment','left',...
        'FontSize',10,...
        'tag','vz_text');
    
    uicontrol('style','pushbutton',...
        'string','Refresh',...
        'units','pixels',...
        'position',[325 10 150 50],...
        'tag','getNdt_button',...
        'callback',@getNdt);
    
    % Angles graph theta, phi, psi (degrees)
    axes('units', 'pixels', ...
        'position', [50 500 250 150], ...
        'xgrid','off',...
        'ygrid','off',...
        'NextPlot','add',...
        'tag','angle');

    % Altitude graph en m
    axes('units', 'pixels', ...
        'position', [380 500 250 150], ...
        'xgrid','off',...
        'ygrid','off',...
        'NextPlot','add',...
        'tag','altitude');

    % Velocities graph vx, vy, vz
    axes('units', 'pixels', ...
        'position', [380 250 250 150], ...
        'xgrid','off',...
        'ygrid','off',...
        'NextPlot','add',...
        'tag','speed');        
        
    global handlesNdt;
    global ndtThread;
    
    ndtThread = ThreadNdt;
    ndtThread.start();
    
    handlesNdt = guihandles(figNdt);
    guidata(figNdt,handlesNdt)
    pause(2);
    getNdt

function getNdt(~,~)
    global handlesNdt;
    global ndtThread;
    t = ((date2num() - ndtThread.getStart())/1000) - 7200; % -7200 -> Dont't know why, it works
    marksize = 5;
    bat = ndtThread.getBattery();
    alt = ndtThread.getAltitude();
    tta = ndtThread.getTheta();
    phi = ndtThread.getPhi();
    psi = ndtThread.getPsi();
    vx = ndtThread.getVx();
    vy = ndtThread.getVy();
    vz = ndtThread.getVz();
        
    if bat > 20
    set(handlesNdt.bat_text,'string',strcat('Battery : ',num2str(bat),' %','.   Suffisant pour voler'));
    else
        set(handlesNdt.bat_text,'string',strcat('Battery : ',num2str(bat),' %','.   Insuffisant pour voler'));
    end
    set(handlesNdt.tta_text,'string',strcat('Theta : ',num2str(tta)));
    set(handlesNdt.phi_text,'string',strcat('Phi : ',num2str(phi)));
    set(handlesNdt.psi_text,'string',strcat('Psi : ',num2str(psi)));
    set(handlesNdt.alt_text,'string',strcat('Altitude : ',num2str(alt)));
    set(handlesNdt.vx_text,'string',strcat('Vx : ',num2str(vx)));
    set(handlesNdt.vy_text,'string',strcat('Vy : ',num2str(vy)));
    set(handlesNdt.vz_text,'string',strcat('Vz : ',num2str(vz)));
    plot(handlesNdt.angle,t,tta,'-ob','MarkerSize',marksize);
    plot(handlesNdt.angle,t,phi,'-or','MarkerSize',marksize);
    plot(handlesNdt.angle,t,psi,'-ok','MarkerSize',marksize);
    plot(handlesNdt.altitude,t,alt,'-ok','MarkerSize',marksize);
    plot(handlesNdt.speed,t,vx,'-ob','MarkerSize',marksize);
    plot(handlesNdt.speed,t,vy,'-or','MarkerSize',marksize);
    plot(handlesNdt.speed,t,vz,'-ok','MarkerSize',marksize);
    drawnow;

function plotNdtFile ()
    global handlesNdt
    try
        fid = fopen('navdata.txt','r');
        a = textscan(fid,'%d %d %f %f %f %d %f %f %f');
        a{1} = a{1}/1000;
        try
            plot(handlesNdt.angle,a{1},a{3},'-b');
            plot(handlesNdt.angle,a{1},a{4},'-r');
            plot(handlesNdt.angle,a{1},a{5},'-k');
            plot(handlesNdt.altitude,a{1},a{6},'-k');
            plot(handlesNdt.speed,a{1},a{7},'-b');
            plot(handlesNdt.speed,a{1},a{8},'-r');
            plot(handlesNdt.speed,a{1},a{9},'-k');
            drawnow;
        catch e2
%             disp(e2);
%             disp('plotFileNdt : The figure is destroyed and can''t be updated.');
        end
    catch e1
%         disp(e1)
%         disp('plotFileNdt : Accessing file navdata.txt failed.');
    end
    
function takeoff(obj,~)
    global handlesNdt;
    
    figNdt = get(obj,'parent');
    handlesNdt = guidata(figNdt);
    
    if strcmp(get(handlesNdt.takeoff_button,'string'),'Start')
        set(handlesNdt.takeoff_button,'string','Stop'); 
        drawnow;
        % if tVol is greater than 30 or 40 seconds, an error in
        % ThreadCmd.java could occur because of the length of double arrays
        % where the informations about the commands are stored.
        tVol = 30;
        loop_counter = 1;
        
        cmdThread = ThreadCmd;
        cmdThread.start();
        tic        
        while(toc<tVol)
            try 
                getNdt;
            catch e
                disp(e);
                disp('getNdt : The figure is destroyed and can''t be updated.');
                break;
            end
            loop_counter = loop_counter + 1;
        end;
        cmdThread.interrupt();
        try
            figNdt = get(obj,'parent');
            handlesNdt = guidata(figNdt);
        catch
        end
        plotNdtFile;
        
        set(handlesNdt.takeoff_button,'string','Start'); 
        drawnow;
        disp(strcat('Updating loops : ',num2str(loop_counter)));

        
        saveTps = cmdThread.getSaveTps();
        saveDrone = cmdThread.getSaveDrone();
        saveHover = cmdThread.getSaveHover();
        saveCmd = cmdThread.getSaveCmd();
        plotVol(saveTps,saveDrone,saveHover,saveCmd);
        
        clear cmdThread;
        
    else
        set(handlesNdt.takeoff_button,'string','Start');
        leave;
    end

function leave(~,~)

    global ndtThread;
    try
        ndtThread.interrupt();
    catch e
        disp('leave : the method ''interrupt'' failed.');
        disp(e);
    end
    fclose(udp('192.168.1.1',5554));
    fclose(udp('192.168.1.1',5556));