CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
XLOGIN = xmacho12
LIBS = -lm

all: primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

primes-i: primes-i.o eratosthenes-i.o error.o bitset.o
	$(CC) $(CFLAGS) -DUSE_INLINE $^ $(LIBS) -o $@

steg-decode: steg-decode.o eratosthenes.o ppm.o error.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
primes-i.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS) -c -DUSE_INLINE $(filter %.c, $^) -o primes-i.o

eratosthenes-i.o: eratosthenes.c bitset.h error.h
	$(CC) $(CFLAGS) -c -DUSE_INLINE -o eratosthenes-i.o $(filter %.c, $^)

zip:
	zip $(XLOGIN).zip *.c *.h Makefile

clean:
	rm -f *.o $(XLOGIN).zip primes primes-i steg-decode
