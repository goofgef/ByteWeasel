CC = gcc
CFLAGS = -Iheaders
SRC = src/zagmate.c
OBJ = $(SRC:.c=.o)
TARGET = zagmate.exe

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(OBJ) -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    del /Q *.o main.exe