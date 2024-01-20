#include "include/slibs.h"
#include "include/slo.h"
#include "include/io.h"


int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Please specify input file.\n");
        return 1;
    }
    slo_compile_file(argv[1]);

    return 0;
}