demo: main.c
	$(CC) main.c -o demo

.PHONY clean:
	rm -f demo
