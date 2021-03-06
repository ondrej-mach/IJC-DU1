CC = gcc
CCFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O0
XLOGIN = xmacho12
LIBS = -lm

all: primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(CCFLAGS) $^ $(LIBS) -o $@

primes-i: primes-i.o eratosthenes-i.o error.o bitset.o
	$(CC) $(CCFLAGS) -DUSE_INLINE $^ $(LIBS) -o $@

steg-decode: steg-decode.o eratosthenes.o ppm.o error.o
	$(CC) $(CCFLAGS) $^ $(LIBS) -o $@

primes.o: primes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)
	
primes-i.o: primes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c -DUSE_INLINE $(filter %.c, $^) -o primes-i.o

steg-decode.o: steg-decode.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

eratosthenes.o: eratosthenes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

eratosthenes-i.o: eratosthenes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c -DUSE_INLINE -o eratosthenes-i.o $(filter %.c, $^)
	
bitset.o: bitset.c bitset.h
	$(CC) $(CCFLAGS) -c -DUSE_INLINE $(filter %.c, $^)

ppm.o: ppm.c error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

error.o: error.c error.h
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)

zip:
	zip $(XLOGIN).zip *.c *.h Makefile

clean:
	rm -f *.o $(XLOGIN).zip primes primes-i steg-decode
