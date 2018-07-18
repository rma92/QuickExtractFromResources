php make_rc.php
windres -O coff rc_temp.rc -o rc.res
mkdir bin
tcc32 main.c rc.res -o bin\output.exe
REM upx --ultra-brute bin\output.exe
