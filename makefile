TARGETNAME=ex.exe

SOURCES= \
  main.c


TARGETLIBS= \
  user32.lib \
  kernel32.lib \
  gdi32.lib \
  legacy_stdio_definitions.lib \
  legacy_stdio_wide_specifiers.lib


TEMP_RC=rc_temp.res

main: $(SOURCES)
  rc $(TEMP_RC)
  cl /nologo -GS- /Os $(SOURCES) $(TEMP_RC) /c /Fomain.obj
  link /nologo main.obj $(TARGETLIBS) /subsystem:windows /align:128 /filealign:128 /OUT:$(TARGETNAME)

full:
  php make_rc.php
  rc $(TEMP_RC)
  cl /nologo -GS- /Os $(SOURCES) $(TEMP_RC) /c /Fomain.obj
  link /nologo main.obj $(TARGETLIBS) /subsystem:windows /align:128 /filealign:128 /OUT:$(TARGETNAME)

clean:
  del main.obj
  del example.exe
