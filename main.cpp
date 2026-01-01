#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <algorithm>

// Function to check if input contains dangerous characters
bool isSafeInput(const std::string& input) {
    if (input.empty() || input.length() < 2) {
        return false;
    }

    // Check for shell metacharacters
    const std::string dangerous = ";|&$`\\\"'<>(){}[]!*?";
    return input.find_first_of(dangerous) == std::string::npos;
}

int main() {
    std::string AppName;
    std::cout << "Enter the name of the app you want to uninstall: ";
    std::getline(std::cin, AppName);

    // Validate input
    if (!isSafeInput(AppName)) {
        std::cerr << "Error: Invalid app name. Please use only alphanumeric characters, spaces, hyphens, and underscores." << std::endl;
        return 1;
    }

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

    if (result.empty()) {
        std::cout << "No files found for '" << AppName << "'." << std::endl;
        return 0;
    }

    // Additional safety: Check if result contains critical paths
    const std::array<std::string, 6> criticalPaths = {
        "/Library\n",
        "/System\n",
        "/Applications\n",
        "/usr\n",
        "/bin\n",
        "/sbin\n"
    };

    // Safety net check
    for (const auto& path : criticalPaths) {
        if (result.find(path) != std::string::npos) {
            std::cerr << "SAFETY NET: Critical system path detected in results!" << std::endl;
            std::cerr << "This program has prevented deletion of critical files." << std::endl;
            std::cerr << "Please report this on GitHub if this seems like a bug." << std::endl;
            std::cout << "\nPress ENTER to exit." << std::endl;
            std::cin.get();
            return 1;
        }
    }

    char yn;
    std::cout << "Would you like to delete these files:\n" << result << "?" << std::endl;
    std::cin >> yn;
    std::cin.ignore(); // Clear newline from buffer

    if (yn == 'y' || yn == 'Y') {
        std::cout << "Deleting files..." << std::endl;
        std::string deleteCommand = command + " -print0 | xargs -0 rm -rf";

        int exitCode = std::system(deleteCommand.c_str());
        if (exitCode == 0) {
            std::cout << "Files deleted successfully." << std::endl;
        } else {
            std::cerr << "Error occurred during deletion." << std::endl;
        }
    } else {
        std::cout << "Deletion cancelled. You may remove these files manually later." << std::endl;
    }

    return 0;
}