CXX=g++
CFLAGS=-I.
DEPS = limits.h
OBJ = main.o db.o 

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)