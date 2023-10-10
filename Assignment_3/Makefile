# Compile options. Το -I<dir> χρειάζεται για να βρει ο gcc τα αρχεία .h
CXXFLAGS = -Wall -Werror -g -std=c++14
COMPILER = g++

# Αρχεία .o, εκτελέσιμο πρόγραμμα και παράμετροι
OBJS =  creature.o #society.o
EXEC = froutopia

creature.o: creature.h creature.cc

#society.o: society.h society.cc

froutopia: $(OBJS) main.cc
		$(COMPILER) $(OBJS) main.cc -o $(EXEC)

clean:
		rm -f $(OBJS) $(EXEC)

run: $(EXEC)
		./$(EXEC) 100 1500 30 5 5