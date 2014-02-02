#include <clang-c/Index.h>

int
main(int argc, char** argv) {
	CXIndex index = clang_createIndex(0, 0);

	const char *args[] = {
         "-I/usr/include",
         "-I."
	};
	int numArgs = sizeof(args) / sizeof(*args);

	CXTranslationUnit tu = clang_parseTranslationUnit(index, "libclang.m", args, numArgs, NULL, 0, CXTranslationUnit_None);

	return 0;
}
