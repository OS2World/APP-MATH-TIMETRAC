timetrac.exe: timetrac.obj timedlgs.obj timetrac.def timetrac.res timetrac.hlp
        link386 /NOI /MAP timetrac.obj timedlgs.obj,,,,timetrac.def;
        rc timetrac.res timetrac.exe

timetrac.hlp: timetrac.ipf timetrac.h
        ipfc timetrac.ipf

timetrac.res: timetrac.rc timetrac.h timedlg.h timetrac.dlg timetrac.ico ttbmp1.bmp
        rc -r timetrac.rc

timetrac.obj: timetrac.c timetrac.h timedlg.h
        icc /c /Ss /Ti- timetrac.c

timedlgs.obj: timedlgs.c timetrac.h timedlg.h
        icc /c /Ss /Ti- timedlgs.c
