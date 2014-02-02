APP=clangulate

XCLIB=`xcode-select --print-path`/Toolchains/XcodeDefault.xctoolchain/usr/lib
# TODO: move clang-c?
#C++=clang
#CC=clang
CPPFLAGS=-I.
#LDFLAGS=-L$(XCLIB) -lclang
LDFLAGS=$(XCLIB)/libclang.dylib -rpath $(XCLIB)

OBJ=clangulate.o

all:$(APP)

$(APP): $(OBJ)

clean:
	rm $(OBJ) $(APP)
