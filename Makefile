BIN=rot
INCDIR=include
OBJDIR=obj
SRCDIR=src

CXX=g++
CXX_CFLAGS=-I$(INCDIR)

ifdef DEBUG
	CXX_CFLAGS += -g3
endif

.PHONY: clean default

default: $(OBJDIR) $(BIN)

$(OBJDIR):
	mkdir -p $@

$(BIN): $(OBJDIR)/Cfg.o $(OBJDIR)/main.o $(OBJDIR)/Range.o $(OBJDIR)/RotCipher.o
	$(CXX) $(CXX_CFLAGS) -o $@ $?

$(OBJDIR)/Cfg.o: $(SRCDIR)/Cfg.cpp $(INCDIR)/Cfg.hpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

$(OBJDIR)/Range.o: $(SRCDIR)/Range.cpp $(INCDIR)/Range.hpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

$(OBJDIR)/RotCipher.o: $(SRCDIR)/RotCipher.cpp $(INCDIR)/RotCipher.hpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

clean:
	rm -fR $(BIN) $(OBJDIR)

