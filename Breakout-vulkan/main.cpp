#include "HelperFunctions.h"
#include "Renderer.h"
//#include "Game.h"

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

int main() {
    HelloTriangleApplication app;

    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    HelperFunctions::sayHi();
    HelperFunctions::checkStackSize();
    try {
        app.run(std::move(game));
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}