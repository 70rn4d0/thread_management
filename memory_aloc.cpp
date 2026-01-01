#include <iostream>
#include <vector>
#include <cstring>
#include <sys/sysinfo.h>
//not complete,
void printMemory() {
    struct sysinfo info;
    sysinfo(&info);

    long totalMB = (info.totalram * info.mem_unit) / (1024 * 1024);
    long freeMB  = (info.freeram  * info.mem_unit) / (1024 * 1024);

    std::cout << "Total RAM:     " << totalMB << " MB\n";
    std::cout << "Available RAM: " << freeMB  << " MB\n";
}

int main() {
    std::cout << "=== Before allocation ===\n";
    printMemory();

    struct sysinfo info;
    sysinfo(&info);

    size_t availableBytes = info.freeram * info.mem_unit;

    size_t allocSize = availableBytes / 2;
    const size_t MAX_ALLOC = 512ULL * 1024 * 1024;

    if (allocSize > MAX_ALLOC)
        allocSize = MAX_ALLOC;

    std::cout << "\nAllocating "
              << allocSize / (1024 * 1024) << " MB...\n";

    try {
        std::vector<char> buffer(allocSize);
        std::memset(buffer.data(), 1, buffer.size());

        std::cout << "\n=== After allocation ===\n";
        printMemory();

        std::cout << "\nPress ENTER to free memory...";
        std::cin.get();

    } catch (...) {
        std::cerr << "Memory allocation failed!\n";
    }

    std::cout << "\n=== After free ===\n";
    printMemory();

    return 0;
}
