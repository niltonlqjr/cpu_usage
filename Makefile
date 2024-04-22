CC 			:= gcc
TARGET 		:= cpu_usage
SOURCES		:= cpu_usage.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(SOURCES)

clean:
	@rm $(TARGET)
