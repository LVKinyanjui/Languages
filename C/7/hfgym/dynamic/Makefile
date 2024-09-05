hfcal.o: ../hfcal.h ../hfcal.c
	gcc -fPIC -c ../hfcal_UK.c -o hfcal.o

libhfcal: hfcal.o
	gcc -shared hfcal.o -o ../../lib/libhfcal.so
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../lib

elliptical.o : ../elliptical.c
	gcc -c ../elliptical.c -o elliptical.o

elliptical: elliptical.o libhfcal
	gcc elliptical.o -L../../lib -lhfcal -o elliptical
