srcdir = src
hdir = $(srcdir)/heads
objdir = obj
bindir = bin
docdir = doc
utils = .gitignore makefile

cc = g++
cflags = -c -g -Wall
lflags =

objects = $(subst $(srcdir),$(objdir),\
$(patsubst %.cc,%.o,$(wildcard $(srcdir)/*.cc)))
target = $(bindir)/sample

default : dirs $(target)

# Compilation to object code
$(objdir)/%.o : $(srcdir)/%.cc $(hdir)/%.h
	$(cc) $(cflags) -o $@ $<

# Compile binary
$(bindir)/sample : $(objects)
	$(cc) $(lflags) -o $@ $^ $(lflags)

# Utilities
dirs :
	@ if [ ! -d $(objdir) ]; then mkdir $(objdir); fi
	@ if [ ! -d $(bindir) ]; then mkdir $(bindir); fi

clean :
	@ rm -f obj/* bin/*

tar :
	@ tar czf bosonsamp.tar.gz $(srcdir) $(docdir) $(utils)