CC = gcc
CFLAGS = -I./include
LDFLAGS = -lssl -lcrypto
SRC = src/u26.c
EXAMPLE = examples/main.c
TARGET = u26_demo

all:
	$(CC) $(SRC) $(EXAMPLE) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)