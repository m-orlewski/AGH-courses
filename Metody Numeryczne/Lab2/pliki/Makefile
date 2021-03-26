CC = gcc
EXEC = main
CFLAGS = $(flag )-I -Wall -lgsl -lgslcblas -lm
SRC = $(wildcard *.c)

all: clean $(EXEC) run

$(EXEC):
	$(CC) $(CFLAGS) $(SRC) -o $@

error: $(EXEC) run
error: flag=-D ERROR

clean:
	rm -rf $(EXEC)

run:
	./$(EXEC)

check:
	valgrind ./$(EXEC)

