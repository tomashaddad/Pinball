#include <iostream>
#include <memory>

#include "RTRApp.h"
#include "exceptions/GLException.h"

int main(int argc, char** argv) {
    try {
        std::unique_ptr<RTRApp> app = std::make_unique<RTRApp>("RTRA1");
        app->run();
    } catch (const GLException& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}