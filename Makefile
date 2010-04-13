BIN=rot
INCDIR=include
OBJDIR=obj
SRCDIR=src

CXX=g++
CXX_CFLAGS=-I$(INCDIR)

.PHONY: clean default

default: $(OBJDIR) $(BIN)

$(OBJDIR):
	mkdir -p $@

$(BIN): $(OBJDIR)/Cfg.o $(OBJDIR)/main.o $(OBJDIR)/Range.o $(OBJDIR)/RotCypher.o
	$(CXX) $(CXX_CFLAGS) -o $@ $?

$(OBJDIR)/Cfg.o: $(SRCDIR)/Cfg.cpp $(INCDIR)/Cfg.hpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

$(OBJDIR)/Range.o: $(SRCDIR)/Range.cpp $(INCDIR)/Range.hpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

$(OBJDIR)/RotCypher.o: $(SRCDIR)/RotCypher.cpp $(INCDIR)/RotCypher.hpp
	$(CXX) $(CXX_CFLAGS) -c -o $@ $<

clean:
	rm -fR $(BIN) $(OBJDIR)

