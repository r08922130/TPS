CC = gcc
CFLAGS = -Wall
DEPS = inc/tps.h inc/inverse.h inc/read_file.h
OBJ = main.o inverse.o tps.o read_file.o

%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< -Iinc

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ -Iinc