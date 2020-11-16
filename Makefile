CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi
LDLIBS = -lodbc

EXE = menu

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o menu_template.o products.o orders.o customers.o




