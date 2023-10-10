JFLAGS = -g
JC = javac
JVM = java
OPT = -O3
WARN = -Wall

Auction: Auction.class

Auction.class: Auction.java
	$(JC) $(JFLAGS) Auction.java

run: Auction.class
	$(JVM) Auction 1000 naturalism good

clean:
	$(RM) *.class