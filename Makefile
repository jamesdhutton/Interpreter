# Declaration of variables
CC		:= g++
CC_FLAGS	:= -std=c++11 -Wall -pedantic
LDFLAGS		:= 

# File names
EXEC		:= interpreter
BINDIR		:= build
SOURCES		= $(wildcard Src/*.cpp)
OBJECTS		= $(SOURCES:Src/%.cpp=$(BINDIR)/%.o)

# bin directory is order-only prerequisit (|), so modification timestamp update 
# won't trigger rebuild. Pre-req for binary and .o so it gets created first
# even with parallel build

.PHONY: all
all: $(EXEC)

# Main target
$(EXEC): $(OBJECTS) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

ifneq "$(MAKECMDGOALS)" "clean"
# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)
endif

# To obtain object files
$(BINDIR)/%.o: Src/%.cpp | $(BINDIR)
	$(CC) -c $(CC_FLAGS) -MP -MMD $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

# To remove generated files
.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS) $(OBJECTS:.o=.d)
