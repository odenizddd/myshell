SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)

bin = myshell

default: $(bin) bello
	make $(bin)
	make bello

$(bin): $(OBJ)
	gcc-13 $^ -o $@

bello: src/bello/bello.c
	cd ./src/bello && make

%.o: %.c
	gcc-13 -o $@ -c $<

clean: $(OBJ)
	rm -f $^
	rm -f $(bin)
	rm -f bello ./src/bello/bello.o
	rm -f .history .aliases

run: $(bin)
	./$(bin)
