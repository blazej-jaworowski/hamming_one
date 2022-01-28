#include <fstream>
#include <iostream>
#include <set>
#include <utility>

std::set<std::pair<int, int>> parse_file(std::string filename) {
    std::ifstream file(filename);
    if (file.fail()) {
        std::cerr << "Failed to open file " << filename << '\n';
        exit(1);
    }

    std::set<std::pair<int, int>> s;
    while (!file.eof()) {
        int a, b;
        file >> a >> b;
        s.insert({a, b});
    }

    file.close();

    return s;
}

bool verify(std::string file1, std::string file2) {
    std::set<std::pair<int, int>> s1 = parse_file(file1);
    std::set<std::pair<int, int>> s2 = parse_file(file2);

    if (s1.size() != s2.size())
        return false;

    for (const auto &e : s1) {
        if (s2.find(e) == s2.end()) {
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Not enough arguments.\n";
        return 1;
    }

    if (verify(argv[1], argv[2])) {
        std::cout << "Results equal\n";
    } else {
        std::cout << "Results different\n";
    }

    return 0;
}