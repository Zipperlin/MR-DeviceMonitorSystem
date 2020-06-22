
PAps.dll: dlldata.obj PALib_p.obj PALib_i.obj
	link /dll /out:PAps.dll /def:PAps.def /entry:DllMain dlldata.obj PALib_p.obj PALib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del PAps.dll
	@del PAps.lib
	@del PAps.exp
	@del dlldata.obj
	@del PALib_p.obj
	@del PALib_i.obj
