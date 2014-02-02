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

    unsigned diagnosticCount = clang_getNumDiagnostics(tu);
	for(unsigned i = 0; i < diagnosticCount; i++) {
		CXDiagnostic diagnostic = clang_getDiagnostic(tu, i);
CXSourceLocation location = clang_getDiagnosticLocation(diagnostic);
clang_getSpellingLocation(location, NULL, &line, &column, NULL);
CXString text = clang_getDiagnosticSpelling(diagnostic);
fprintf(stderr, "%u:%u: %s\n", line, column, clang_getCString(text));
clang_disposeString(text);
	}


	return 0;
}
