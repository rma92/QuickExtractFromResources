windres -O coff rc.rc -o rc.res
tcc32 main_micro.c rc.res -o output_micro.exe
upx --ultra-brute output_micro.exe
