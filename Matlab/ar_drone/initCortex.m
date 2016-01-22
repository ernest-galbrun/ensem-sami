function [] = InitCortex()
    [pathstr] = fileparts(which('khepera3.m'));
    dllPath = fullfile(pathstr,'dll');
    setenv('PATH',[getenv('PATH') ';' fullfile(dllPath,'64bits')])
    loadlibrary('khepera3clib.dll','khepera3clib.h')
end

