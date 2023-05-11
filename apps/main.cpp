#include "primer.h"

#include <iostream>
#include <stdexcept>

int main() {

    try {
        primer_main();
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }

    //return EXIT_SUCCESS;
    return 0;
}
