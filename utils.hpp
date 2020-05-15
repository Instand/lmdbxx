#include <string>
#include <exception>
#include <iostream>
#include <filesystem>

namespace cs {
class FileUtils {
public:
    static bool isPathExist(const std::string& path) {
        std::filesystem::path p(path);
        bool res = false;

        try {
            res = std::filesystem::is_directory(p);
        }
        catch (const std::exception& e) {
            std::cout << "Is path exists exception " << e.what() << std::endl;
        }

        return res;
    }

    static bool createPath(const std::string& path) {
        std::filesystem::path p(path);
        bool res = false;

        try {
            res = std::filesystem::create_directory(p);
        }
        catch (const std::exception& e) {
            std::cout << "Create path exception " << e.what() << std::endl;
        }

        return res;
    }

    static bool createPathIfNoExist(const std::string& path) {
        if (isPathExist(path)) {
            return true;
        }

        return createPath(path);
    }
};
}
