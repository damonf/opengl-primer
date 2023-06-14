#include "build_primer.h"

#include <iostream>
#include <stdexcept>

int main() {

    try {
        auto primer = primer::build_primer();
        primer.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
