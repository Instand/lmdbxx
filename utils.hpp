#include <string>
#include <exception>
#include <iostream>
#include <filesystem>

namespace cs {
template <typename T>
struct IsArray : std::false_type {};

template <typename T, size_t size>
struct IsArray<std::array<T, size>> : std::true_type {};

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
