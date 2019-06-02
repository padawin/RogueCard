CC = $(CROSS_COMPILE)g++ -std=c++11
CFLAGS = -g -O2 -Wall -Wmissing-declarations -Weffc++ \
	-pedantic -pedantic-errors -Wextra -Wcast-align \
	-Wcast-qual -Wconversion -Wsign-conversion \
	-Wdisabled-optimization \
	-Werror -Wfloat-equal -Wformat=2 \
	-Wformat-nonliteral -Wformat-security \
	-Wformat-y2k \
	-Wimport -Winit-self -Winline \
	-Winvalid-pch \
	-Wlong-long \
	-Wmissing-field-initializers -Wmissing-format-attribute \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked -Wpointer-arith \
	-Wredundant-decls \
	-Wshadow -Wstack-protector \
	-Wstrict-aliasing=2 -Wswitch-default \
	-Wswitch-enum \
	-Wunreachable-code -Wunused \
	-Wunused-parameter \
	-Wvariadic-macros \
	-Wwrite-strings

CFLAGS += -I$(SRCDIR)/game -I$(SRCDIR)/common -I$(SRCDIR)/rogue-card -I$(SRCDIR)/sdl2
LIBS = -lSDL2 -lSDL2_image -ldl

PROG = rogue-card
SRCDIR = src
BINDIR = bin
BUILDDIR = build

DEP := $(shell find $(SRCDIR)/game $(SRCDIR)/common $(SRCDIR)/rogue-card $(SRCDIR)/sdl2 -type f -name '*.hpp')
SRC := $(shell find $(SRCDIR)/game $(SRCDIR)/common $(SRCDIR)/rogue-card $(SRCDIR)/sdl2 -type f -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEP)
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(CFLAGS)

all: prepare $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS)

prepare:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)
