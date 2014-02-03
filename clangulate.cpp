#include <clang-c/Index.h>
#include <stdio.h>
#include <assert.h>

// starting point
// https://mikeash.com/pyblog/friday-qa-2014-01-24-introduction-to-libclang.html
// Xcode configuration
// http://therealbnut.wordpress.com/2012/01/01/setting-xcode-4-0-environment-variables-from-a-script/

int
main(int argc, char** argv) {
	assert(argc == 2);
	
	CXIndex index = clang_createIndex(0, 0);

	const char *args[] = {
         "-I/usr/include",
         "-I."
	};
	int numArgs = sizeof(args) / sizeof(*args);

	CXTranslationUnit tu = clang_parseTranslationUnit(index, argv[1], args, numArgs, NULL, 0, CXTranslationUnit_None);

    unsigned diagnosticCount = clang_getNumDiagnostics(tu);
	for(unsigned i = 0; i < diagnosticCount; i++) {
		CXDiagnostic diagnostic = clang_getDiagnostic(tu, i);

		CXSourceLocation location = clang_getDiagnosticLocation(diagnostic);
		
		unsigned line, column;	// WTF clang, would it kill you to write int?
		clang_getSpellingLocation(location, NULL, &line, &column, NULL);
		CXString text = clang_getDiagnosticSpelling(diagnostic);
		fprintf(stderr, "%u:%u: %s\n", line, column, clang_getCString(text));
		clang_disposeString(text);
	}

	int	res = clang_visitChildrenWithBlock(clang_getTranslationUnitCursor(tu), ^(CXCursor cursor, CXCursor parent){
		CXCursorKind	kind = clang_getCursorKind(cursor);
		CXString	ks = clang_getCursorKindSpelling(kind);
		fprintf(stderr, "kind: %s (%i)\n", clang_getCString(ks), kind);
		clang_disposeString(ks);
		
		return CXChildVisit_Continue;
		return CXChildVisit_Recurse;
	});
	
	assert(0 == res);

	return 0;
}
