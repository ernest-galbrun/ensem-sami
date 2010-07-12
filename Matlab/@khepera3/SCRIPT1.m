%-- 12/07/10 16:19 --%
loadlibrary('khepera3.h','khepera3.dll')
loadlibrary('khepera3.dll','khepera3.h')
a = voidPtrPtr
p = libpointer
LaunchKhepera(2,2,*p)
p = libpointer('voidPtrPtr')
LaunchKhepera(2,2,p)
calllib('khepera3','LaunchKhepera',2,2,p)
calllib('khepera3','SetSpeed',*p,2,2)
calllib('khepera3','SetSpeed',get(p,'value'),2,2)
