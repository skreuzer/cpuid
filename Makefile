CFLAGS+=	-std=c99 -Wall -I. -g -D_BSD_SOURCE
PREFIX?=	/var/cfengine/modules

SRC=	cpuid.c

OBJ=	$(SRC:.c=.o)
EXE=	$(SRC:.c=)

all:	$(EXE)

$(OBJ):
	${CC} ${CFLAGS} -c $<

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

install: $(EXE)
	install -m 755 $(EXE) $(PREFIX)

clean:
	rm $(OBJ) $(EXE)
