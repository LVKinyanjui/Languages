hfcal.o: hfcal.h hfcal.c
	gcc -c hfcal.c

elliptical.o: elliptical.c hfcal.h
	gcc -c elliptical.c

elliptical: hfcal.o elliptical.o
	gcc hfcal.o elliptical.o -o elliptical

libhfgym: hfcal.o elliptical.o
	ar -rcs libhfgym hfcal.o elliptical.o
	mv libhfgym ../lib/
