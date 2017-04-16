CC=gcc
CFLAGS=-Wall
OPTF=-O0 -fPIC -std=c99 -g  -pedantic

all: fm_fina libiconal.so

fm_fina: main.c libiconal.so
	$(CC) $< -o $@ $(OPTF) -I. -L. -liconal -lm
libiconal.so: fast_marching.o heap.o iconal.o
	$(CC) $(OPTF) -shared $^ -o $@

fast_marching.o: fast_marching.c iconal.h
	$(CC) $(OPTF) -c $< -o $@

heap.o: heap.c iconal.h
	$(CC) $(OPTF) -c $< -o $@

iconal.o: iconal.c iconal.h
		$(CC) $(OPTF) -c $< -o $@
clean:
	rm -rf *.o
#export LD_LIBRARY_PATH=:$LD_LIBRARY_PATH fm_fina
