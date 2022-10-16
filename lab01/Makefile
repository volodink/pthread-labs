all: clean prepare
	gcc -O2 -std=c99 -o bin/lab01 lab01.c -pthread

clean:
	rm -rf bin

prepare:
	mkdir -p bin

run:
	./bin/lab01
