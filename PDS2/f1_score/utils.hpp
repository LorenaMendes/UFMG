#ifndef ASSERT
#include <iostream>
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion failed in " << __PRETTY_FUNCTION__ << endl  << message << std::endl; \
            exit(-1); \
        } \
    } while (false)

#endif