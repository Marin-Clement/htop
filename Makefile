CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lncurses
SRC_FILES = main.c cpu_info.c display.c processes.c system_info.c
OBJ_FILES = $(SRC_FILES:.c=.o)
TARGET = htop

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean
