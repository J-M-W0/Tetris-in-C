CC := clang
CFLAGS := -I/opt/homebrew/include -Wall -std=c17
LFLAGS := -L/opt/homebrew/lib -lsdl2 -lsdl2_image -lsdl2_ttf

CFILES := main.c
CFILES += tetrisdef.c
CFILES += gridfunc.c
CFILES += tetrisfunc.c
CFILES += junzhefunc.c

OBJS   := main.o
OBJS   += tetrisdef.o
OBJS   += gridfunc.o
OBJS   += tetrisfunc.o
OBJS   += junzhefunc.o

TARGET := tetris

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf ${TARGET} ${OBJS}
