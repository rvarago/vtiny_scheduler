TARGET		= vtiny_scheduler

SRCDIR		= src
OBJDIR		= obj
BINDIR		= bin

SOURCES  	:= $(wildcard $(SRCDIR)/*.c)
INCLUDES 	:= $(wildcard $(SRCDIR)/*.h)
OBJECTS  	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BIN		:= $(BINDIR)/$(TARGET)

CC		= gcc
CFLAGS		= -g -Wall -pedantic
LFLAGS		=

RMCMD		= rm
RMFLAGS		= -rf

MKDIRCMD	= mkdir
MKDIRFLAGS	= -p

PRINTCMD	= echo

.PHONY: all
.PHONY: clean

all: $(OBJDIR) $(BINDIR) $(BIN)

$(BIN): $(OBJECTS)
	@$(CC) -o $@ $(LFLAGS) $(OBJECTS)
	@$(PRINTCMD) "Linking "$^" complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(PRINTCMD) "Compiled "$<" to "$@" successfully!"

$(BINDIR):
	$(MKDIRCMD) $(MKDIRFLAGS) $@
	@$(PRINTCMD) "Created "$@" successfully!" 

$(OBJDIR):
	$(MKDIRCMD) $(MKDIRFLAGS) $@
	@$(PRINTCMD) "Created "$@" successfully!" 

clean: 
	$(RMCMD) $(RMFLAGS) $(OBJDIR) $(BINDIR)
