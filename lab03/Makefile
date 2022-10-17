all: clean prepare
	gcc -O2 -std=c17 -o bin/lab03 lab03.c -pthread
	gcc -O2 -std=c17 -o bin/lab03_queue lab03_queue.c -pthread

clean:
	rm -rf bin

prepare:
	mkdir -p bin

run:
	./bin/lab03

run_queue:
	./bin/lab03_queue
