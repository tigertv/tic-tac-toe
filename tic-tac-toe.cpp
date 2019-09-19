#include <iostream>
#include <string>
#include <vector>
#include "Game.h"

void show_usage(std::string name) {
    std::cerr << "Usage: " << name << " <option(s)>"
        << "Options:" << std::endl
        << "\t-h,--help\t\tShow this help message" << std::endl
        << "\t-s,--size SIZE\tSpecify the size of the board (default = 3)" << std::endl
        << "\t-l,--line LENGTH\tSpecify the length of the line to win (default = 3)" << std::endl;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv+argc);
    int size = 3;
    int line = 3;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(args[0]);
            return 0;
        } else if ((arg == "-s") || (arg == "--size")) {
            if (i + 1 < argc) {
                try {
                    size = std::stoi(args[++i]);
                } catch(std::invalid_argument& e){
                    std::cerr << "--size option requires an integer." << std::endl;
                    return 1;
                } catch(std::out_of_range& e){
                    std::cerr << "--size option requires an integer." << std::endl;
                    return 1;
                }

            } else {
                std::cerr << "--size option requires one argument." << std::endl;
                return 1;
            }
        } else if ((arg == "-l") || (arg == "--line")) {
            if (i + 1 < argc) {
                try {
                    line = std::stoi(args[++i]);
                } catch(std::invalid_argument& e){
                    std::cerr << "--line option requires an integer." << std::endl;
                    return 1;
                } catch(std::out_of_range& e){
                    std::cerr << "--line option requires an integer." << std::endl;
                    return 1;
                }

            } else {
                std::cerr << "--line option requires one argument." << std::endl;
                return 1;
            }
        }
    }

    Game game(size, line);
    game.run();
    return 0;
}
