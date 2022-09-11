all:
	gcc -Os -s -o bf bf.c
	gcc -Os -s -o b2c b2c.c

test:
	./bf examples/hello.b
	./b2c examples/hello.b examples/hello.c