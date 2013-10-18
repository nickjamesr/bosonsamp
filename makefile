srcdir = src
hdir = $(srcdir)/heads
objdir = obj
bindir = bin
docdir = doc
utils = .gitignore makefile

cc = g++
debug =
opt = -O2
cflags = -c -fPIC $(debug) $(opt) -Wall
lflags = -lgsl -lgslcblas -lm -lcurses

objects = $(subst $(srcdir),$(objdir),\
$(patsubst %.cc,%.o,$(wildcard $(srcdir)/*.cc)))
target = $(bindir)/libbosonsamp.so

default : dirs $(target)

# Compilation to object code
$(objdir)/%.o : $(srcdir)/%.cc $(hdir)/%.h
	$(cc) $(cflags) -o $@ $<

# Compile binary
$(bindir)/sample : $(objects)
	$(cc) $(lflags) -o $@ $^ $(lflags)

# Build .so
$(bindir)/libbosonsamp.so : $(objects)
	ar cr $@ $^

# Install header and object files to default search directories
install : $(target)
	@ rm -f /usr/lib/libbosonsamp.so
	@ rm -rf /usr/include/bosonsamp
	@ cd /usr/include; ln -s $(CURDIR)/$(hdir) bosonsamp
	@ cd /usr/lib; ln -s $(CURDIR)/$(bindir)/libbosonsamp.so

uninstall :
	@ rm -f /usr/lib/libbosonsamp.so
	@ rm -rf /usr/include/bosonsamp

# Utilities
dirs :
	@ if [ ! -d $(objdir) ]; then mkdir $(objdir); fi
	@ if [ ! -d $(bindir) ]; then mkdir $(bindir); fi

clean :
	@ rm -f obj/* bin/*

tar :
	@ tar czf bosonsamp.tar.gz $(srcdir) $(docdir) $(utils)
