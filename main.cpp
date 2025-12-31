#include <iostream>
#include <cstdlib>
#include <string>
#include <array>

int main() {
    std::string AppName;
    std::cout << "Enter the name of the app you want to uninstall: ";
    std::getline(std::cin, AppName);

    // Construct the find command dynamically
    std::string command = "find ~/Library/Application\\ Support ~/Library/Preferences ~/Library/Caches ~/Library/Containers "
                          "-maxdepth 2 -iname '*" + AppName + "*' 2>/dev/null";

    // Open a pipe to read the command output
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run command." << std::endl;
        return 1;
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);

    std::cout << "App paths in ~/Library are:\n" << result << std::endl;
    std::cout << "For safety, this app will not automatically delete anything. Please delete these files manually.\n" << std::endl;
    std::cout << "Press ENTER to exit\n" << std::endl;
    getchar();
    return 0;
}
