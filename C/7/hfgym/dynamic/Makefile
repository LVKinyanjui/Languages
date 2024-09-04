hfcal.o: ../hfcal.h ../hfcal.c
	gcc -fPIC -c ../hfcal.c -o hfcal.o

libhfcal: hfcal.o
	gcc -shared hfcal.o -o ../../lib/libhfcal.so
