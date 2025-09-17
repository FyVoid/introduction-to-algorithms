CC = clang
CXX = clang++
CFLAGS = -std=c++23 -Wall -Wextra

SOURCES += $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

run: $(TARGET)
	./$(TARGET)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)