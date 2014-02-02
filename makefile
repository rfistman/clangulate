APP=clangulate

XCLIB=`xcode-select --print-path`/Toolchains/XcodeDefault.xctoolchain/usr/lib
# TODO: move clang-c?
CPPFLAGS=-I.
LDFLAGS=-L$(XCLIB) -lclang

OBJ=clangulate.o

all:$(APP)

$(APP): $(OBJ)

clean:
	rm $(OBJ) $(APP)
