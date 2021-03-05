CC = gcc
CCFLAGS = -g -std=c11 -pedantic -Wall -Wextra -Winline
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
	$(CC) $(CCFLAGS) -c $^

steg-decode.o: steg-decode.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $^

eratosthenes.o: eratosthenes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c $^

eratosthenes-i.o: eratosthenes.c bitset.h error.h
	$(CC) $(CCFLAGS) -c -DUSE_INLINE $^ -o eratosthenes-i.o

ppm.o: ppm.c error.h
	$(CC) $(CCFLAGS) -c $^

error.o: error.c error.h
	$(CC) $(CCFLAGS) -c $^

zip:
	zip $(XLOGIN).zip *.c *.h Makefile

clean:
	rm -f *.o $(XLOGIN).zip primes primes-i steg-decode
