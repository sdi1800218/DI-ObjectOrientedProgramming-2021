# Compile options. Το -I<dir> χρειάζεται για να βρει ο gcc τα αρχεία .h
CXXFLAGS = -Wall -Werror -g
COMPILER = g++

# Αρχεία .o, εκτελέσιμο πρόγραμμα και παράμετροι
OBJS =  trapeza.o
EXEC = banking

trapeza.o: trapeza.h trapeza.cc

# banking.o: main.cc

banking: $(OBJS) main.cc
		$(COMPILER) $(OBJS) main.cc -o $(EXEC)

clean:
		rm -f $(OBJS) $(EXEC)

run: $(EXEC)
		./$(EXEC) 20 20 20 20