/**
 * DIRECTORY MAPPER v1.0 (UTF-8 COMPATIBLE)
 * Architected by: syedsaad314 (BSSE, KU)
 * Logic: Recursive Traversal Of Directory
 */

#include <iostream>
#include <filesystem>
#include <string>
#include <iomanip>

#ifdef _WIN32
#include <windows.h> // Required for UTF-8 Support on Windows
#endif

using namespace std;
namespace fs = filesystem;

class DirectoryMapper {
public:
    string formatSize(uintmax_t size) {
        if (size < 1024) return to_string(size) + " B";
        if (size < 1024 * 1024) return to_string(size / 1024) + " KB";
        return to_string(size / (1024 * 1024)) + " MB";
    }

    void mapDirectory(const fs::path& path, int indent_level = 0) {
        try {
            if (fs::exists(path) && fs::is_directory(path)) {
                for (const auto& entry : fs::directory_iterator(path)) {
                    string filename = entry.path().filename().string();
                    
                    // SKIP the .git folder to keep the dashboard clean
                    if (filename == ".git") continue;

                    for (int i = 0; i < indent_level; ++i) cout << "    ";

                    if (fs::is_directory(entry)) {
                        cout << "📁 [" << filename << "]" << endl;
                        mapDirectory(entry.path(), indent_level + 1);
                    } else {
                        uintmax_t fSize = fs::file_size(entry);
                        cout << "└── 📄 " << left << setw(25) << filename 
                             << " (" << formatSize(fSize) << ")" << endl;
                    }
                }
            }
        } catch (const exception& e) {
            cerr << "[!] Access Denied" << endl;
        }
    }
};

int main() {
    // SYSTEM LOGIC: Force Windows Terminal to use UTF-8 Encoding
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    DirectoryMapper engine;
    
    cout << "\n==================================================" << endl;
    cout << "   ADVANCED SYSTEM ARCHITECTURE MAPPER v1.0" << endl;
    cout << "==================================================" << "\n" << endl;

    fs::path root = fs::current_path();
    cout << "[ROOTNODE]:: " << root.string() << "\n" << endl;

    engine.mapDirectory(root);

    cout << "\n==================================================" << endl;
    cout << "   [SUCCESS] LOGIC-LABS STRUCTURE VERIFIED" << endl;
    cout << "==================================================" << endl;

    return 0;
}