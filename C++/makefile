CC = g++
LD = g++


CFLAGS  = -c -Wall
LDFLAGS = 


SOURCES    = main.cpp  multiplicationAlg.cpp  
OBJECTS    = $(SOURCES:.cpp = .o)
EXECUTABLE = main


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(LD)  $(LDFLAGS) $(OBJECTS)  -o  $@

.cpp.o:
	$(CC)  $(CFLAGS)  $<  -o  $@


clean:
	rm  -rf  *.o  main
