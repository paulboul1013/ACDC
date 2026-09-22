CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g

TARGET = acdc
OBJS = main.o scan.o expr.o stmt.o misc.o tree.o gen.o cg.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c main.c

scan.o: scan.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c scan.c

expr.o: expr.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c expr.c

stmt.o: stmt.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c stmt.c

misc.o: misc.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c misc.c

tree.o: tree.c defs.h decl.h
	$(CC) $(CFLAGS) -c tree.c

gen.o: gen.c defs.h decl.h
	$(CC) $(CFLAGS) -c gen.c

cg.o: cg.c data.h decl.h
	$(CC) $(CFLAGS) -c cg.c

out: out.s
	$(CC) -o out out.s

test: $(TARGET)
	./$(TARGET) input01
	$(CC) -o out out.s
	./out

clean:
	rm -f $(TARGET) out out.s $(OBJS)

.PHONY: test clean
