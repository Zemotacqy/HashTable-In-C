CC = gcc
CFLAGS = -std=c11 -Wall -fmax-errors=10

MAIN = program
OBJFILES = utils.o hashtable.o program.o

all: $(MAIN)

$(MAIN): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(MAIN)
