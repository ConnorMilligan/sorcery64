SRC_DIR = src
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCES))

PROGRAM = sorcery64
CC65_TARGET = c64
CC = cl65
CFLAGS = -t $(CC65_TARGET) -O
LDFLAGS = -t $(CC65_TARGET) -m $(BIN_DIR)/$(PROGRAM).map

########################################

.PHONY: all clean

all: $(BIN_DIR)/$(PROGRAM)

-include $(DEPS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BIN_DIR)/$(PROGRAM): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@.prg $^

clean:
	$(RM) -r $(BIN_DIR)
