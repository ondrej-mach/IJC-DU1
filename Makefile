CC = gcc
CCFLAGS = -g -std=c11 -pedantic -Wall -Wextra -Winline -O0
XLOGIN = xmacho12
LIBS = -lm

all: primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBS)

primes-i: primes.o eratosthenes-i.o error.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBS)

steg-decode: steg-decode.o eratosthenes.o ppm.o error.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBS)

primes.o: primes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

steg-decode.o: steg-decode.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

eratosthenes.o: eratosthenes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

eratosthenes-i.o: eratosthenes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c -DUSE_INLINE -o eratosthenes-i.o $(filter %.c, $^)

ppm.o: ppm.c error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

error.o: error.c error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

zip:
	zip $(XLOGIN).zip *.c *.h Makefile

clean:
	rm -f *.o $(XLOGIN).zip primes primes-i steg-decode
