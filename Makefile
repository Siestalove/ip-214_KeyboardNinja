APP_NAME = main
LIB_NAME = lib

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -I thirdparty -MP -MMD
LDFLAGS =
LDLIBS = -lm

NCURSESW_CFLAGS := $(shell pkg-config ncursesw --cflags)
NCURSESW_LDLIBS := $(shell pkg-config ncursesw --libs)

CPPFLAGS += $(NCURSESW_CFLAGS)
LDFLAGS += $(NCURSESW_LDLIBS)


CPPFLAGS += $(NCURSESW_CFLAGS)
LDLIBS += $(NCURSESW_LDLIBS)

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(LIB_NAME).a

SRC_EXT = c

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all clean run folders

all: folders $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	$(RM) $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(APP_PATH)

folders:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)