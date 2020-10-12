CFLAGS =  -w -fopenmp
CC = g++

SOURCE_PATH = src/
BUILD_PATH = build/
OBJ_SUFIX = .o

NAME = jaspion
TARGET = $(BUILD_PATH)$(NAME)

SRC = jaspion brain_network matrix
_SRC = $(addprefix $(BUILD_PATH), $(addsuffix $(OBJ_SUFIX), $(SRC)))

all: $(_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(_SRC)
	@echo "$(NAME) has been built"

$(BUILD_PATH)%.o: $(SOURCE_PATH)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm build/*.o

run:
	./build/jaspion.exe
