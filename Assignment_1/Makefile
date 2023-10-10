# Compile options. Το -I<dir> χρειάζεται για να βρει ο gcc τα αρχεία .h
CXXFLAGS = -Wall -Werror -g
COMPILER = g++

# Αρχεία .o, εκτελέσιμο πρόγραμμα και παράμετροι
OBJS = bookcase.o #vivliothiki.o
EXEC = vivliothiki

bookcase.o: bookcase.h bookcase.cpp

# vivliothiki.o: main.cpp

vivliothiki: $(OBJS) main.cpp
		$(COMPILER) $(OBJS) main.cpp -o $(EXEC)

clean:
		rm -f $(OBJS) $(EXEC)

run: $(EXEC)
		./$(EXEC) 1000 1000 1000 1000