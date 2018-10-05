TARGET = piperunner

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c
	cc -Os -Wall -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	cc $(OBJECTS) -Os -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
