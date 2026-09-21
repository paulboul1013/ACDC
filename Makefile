CC      = cc
CFLAGS  = -std=c17 -Wall -Wextra -Wpedantic -g

TARGET  = acdc
OBJS    = main.o scan.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c main.c

scan.o: scan.c defs.h data.h decl.h
	$(CC) $(CFLAGS) -c scan.c

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: clean
