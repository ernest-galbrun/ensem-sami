function varargout = main(varargin)
% MAIN M-file for main.fig
%      MAIN, by itself, creates a new MAIN or raises the existing
%      singleton*.
%
%      H = MAIN returns the handle to a new MAIN or the handle to
%      the existing singleton*.
%
%      MAIN('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MAIN.M with the given input arguments.
%
%      MAIN('Property','Value',...) creates a new MAIN or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before main_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to main_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help main

% Last Modified by GUIDE v2.5 11-Jun-2010 10:51:47

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @main_OpeningFcn, ...
                   'gui_OutputFcn',  @main_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before main is made visible.

function main_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to main (see VARARGIN)

% Choose default command line output for main
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);


k3 = khepera3([handles.leftPosition handles.rightPosition handles.leftSpeed handles.rightSpeed]);
set(gcf,'userdata',k3);

% UIWAIT makes main wait for user response (see UIRESUME)
% uiwait(handles.Main);


% --- Outputs from this function are returned to the command line.
function varargout = main_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function ip_Callback(hObject, eventdata, handles)
% hObject    handle to ip (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ip as text
%        str2double(get(hObject,'String')) returns contents of ip as a double


% --- Executes during object creation, after setting all properties.
function ip_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ip (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function ip_KeyPressFcn(hObject, eventdata, handles)
if strcmp(eventdata.Key,'return')
    connect_Callback(hObject, eventdata, handles);
end

% --- Executes on button press in connect.
function connect_Callback(hObject, eventdata, handles)
% hObject    handle to connect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
k3 = get(gcf,'userdata');
if k3.Connect(get(handles.ip,'String'),'193.49.136.176',1,handles.connectionStatus)==0
    modes = k3.GetMode();
    PID = k3.GetPID();
    set(handles.leftControlMode,'Value',modes(1));
    set(handles.rightControlMode,'Value',modes(2));
    set(handles.PID,'Data',PID');
    k3.RunAcquisition('start');
end
set(gcf,'userdata',k3);



% --- Executes on selection change in leftControlMode.
function leftControlMode_Callback(hObject, eventdata, handles)
SetControlMode(handles);

% --- Executes on selection change in rightControlMode.
function rightControlMode_Callback(hObject, eventdata, handles)
SetControlMode(handles);

function SetControlMode(handles)
modes = struct('Open_Loop',0,'Position',1,'Speed',2,'Torque',3);
modeLeft = get(handles.leftControlMode,'Value');
modeRight = get(handles.rightControlMode,'Value');
k3 = get(gcf,'userdata');
k3.RunAcquisition('stop');
k3.SetMode(modeLeft, modeRight);
modes = k3.GetMode();
PID = k3.GetPID();
set(handles.leftControlMode,'Value',modes(1));
set(handles.rightControlMode,'Value',modes(2));
set(handles.PID,'Data',PID');
k3.RunAcquisition('start');

% --- Executes during object creation, after setting all properties.
function leftControlMode_CreateFcn(hObject, eventdata, handles)
% hObject    handle to leftControlMode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




% --- Executes during object creation, after setting all properties.
function rightControlMode_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rightControlMode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function targetLeft_Callback(hObject, eventdata, handles)


function targetLeft_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function targetRight_Callback(hObject, eventdata, handles)


function targetRight_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function goto_Callback(hObject, eventdata, handles)
    k3 = get(gcf,'userdata');
    k3.RunAcquisition('stop');
    k3.SetPoint(khepera3.RWtoK3(get(handles.leftControlMode,'Value'),str2num(get(handles.targetLeft,'String'))),...
                khepera3.RWtoK3(get(handles.rightControlMode,'Value'),str2num(get(handles.targetRight,'String'))));
    k3.RunAcquisition('start');


function recordPulse_Callback(hObject, eventdata, handles)
k3 = get(gcf,'userdata');
k3.RunAcquisition('stop');
a=get(handles.stepData,'data');
result = k3.StepAcquisition(get(handles.stepData,'data'),...
        [get(handles.measureTypeL,'value') get(handles.measureTypeR,'value')],...
        get(handles.leftControlMode,'value'), get(handles.rightControlMode,'value'));
DrawStep(handles.stepPlot,get(handles.stepData,'data'),result);
k3.RunAcquisition('start');

function popupmenu3_CreateFcn(hObject, eventdata, handles)

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function currentPositionLeft_Callback(hObject, eventdata, handles)


function currentPositionLeft_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function currentPositionRight_Callback(hObject, eventdata, handles)


function currentPositionRight_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function setCurrentPosition_Callback(hObject, eventdata, handles)
k3 = get(gcf,'userdata');
k3.RunAcquisition('stop');
k3.SetPosition(khepera3.RWtoK3(2,str2num(get(handles.currentPositionLeft,'string'))),...
               khepera3.RWtoK3(2,str2num(get(handles.currentPositionRight,'string'))));
k3.RunAcquisition('start');

function Main_CloseRequestFcn(hObject, eventdata, handles)
k3 = get(gcf,'userdata');
if (k3.id~=0)
    k3.StopMotors();
    k3.Disconnect();
end
delete(k3);
set(gcf,'userdata',[]);
delete(hObject);

function PID_CellEditCallback(hObject, eventdata, handles)
k3 = get(gcf,'userdata');
k3.RunAcquisition('stop');
k3.SetPID(get(handles.PID,'data'));
k3.RunAcquisition('start');

function startMotors_Callback(hObject, eventdata, handles)
k3 = get(gcf,'userdata');
k3.RunAcquisition('stop');
k3.StartMotors();
k3.RunAcquisition('start');

function stopMotors_Callback(hObject, eventdata, handles)
k3 = get(gcf,'userdata');
k3.RunAcquisition('stop');
k3.StopMotors();
k3.RunAcquisition('start');


function measureTypeL_Callback(hObject, eventdata, handles)


function measureTypeL_CreateFcn(hObject, eventdata, handles)

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function measureTypeR_Callback(hObject, eventdata, handles)


function measureTypeR_CreateFcn(hObject, eventdata, handles)

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
