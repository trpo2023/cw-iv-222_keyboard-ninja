APP_NAME = ninja_play
LIB_NAME = ninja_lib
TEST_NAME = ninja_test

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -I thirdparty -MP -MMD
LDFLAGS =
LDLIBS = -lm -lncurses

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

SRC_EXT = c

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

TEST_SOURCES = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)')
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) 

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: test
test: $(TEST_PATH)

$(TEST_PATH): $(TEST_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) 
	
.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH) $(TEST_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

.PHONY: running
running:
	./$(APP_PATH)

.PHONY: testing
testing:
	./$(TEST_PATH)