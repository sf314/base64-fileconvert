
# FLAGS=\
# -Wall \
# -Werror

INCLUDES=\
-I.

SOURCES=\
main.c \
fileconvert.c

INPUT=testfile.txt

OUTPUT=f2b64

all:
	gcc $(FLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT)
	
run:
	./$(OUTPUT) $(INPUT)

clean:
	rm $(OUTPUT)