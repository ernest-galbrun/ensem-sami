function num = date2num()
% date = datestr(now,'ddHHMMSSFFF');
% num = 86400000*str2double(date(1:2))+3600000*str2double(date(3:4))+60000*str2double(date(5:6))+1000*str2double(date(7:8))+str2double(date(9:11));
num = 8.64e7*(now - datenum('1970','yyyy'));