all: clean prepare
	gcc -O2 -std=c99 -o bin/lab02 lab02.c -pthread

clean:
	rm -rf bin

prepare:
	mkdir -p bin

run:
	./bin/lab02
