# Makefile for Keepaway tools
# Gregory Kuhlmann, 2002

TARGET = hist winsum kwyzipper
CC = g++

all:: $(TARGET)

hist: hist.cc
	$(CC) hist.cc -o hist

winsum: winsum.cc
	$(CC) winsum.cc -o winsum

kwyzipper: kwyzipper.cc
	$(CC) kwyzipper.cc -o kwyzipper

clean:
	rm -f $(TARGET) *~ 1.out 1.hist graph.eps hist.eps