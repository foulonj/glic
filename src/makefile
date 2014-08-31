CC=c++
CFLAGS=-Wall
EXEC_NAME=main
INCLUDES=
LIBS=
OBJ_FILES=properties.o light.o object.o main.o

all:$(EXEC_NAME)

clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<	
