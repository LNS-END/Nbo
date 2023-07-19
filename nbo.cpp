#include <iostream>
#include <fstream>
#include <cstdint>
#include <arpa/inet.h>

uint32_t readNumber(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(1);
    }

    uint32_t number;
    file.read(reinterpret_cast<char*>(&number), sizeof(number));
    file.close();

    return ntohl(number);  // 네트워크 바이트 순서를 호스트 바이트 순서로 변환
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "syntax: add-nbo <file1> <file2>" << std::endl;
        std::cout << "sample: add-nbo a.bin b.bin" << std::endl;
        return 1;
    }

    const std::string file1(argv[1]);
    const std::string file2(argv[2]);

    uint32_t num1 = readNumber(file1);
    uint32_t num2 = readNumber(file2);
    uint32_t result = num1 + num2;

    std::cout << std::dec << num1 << "(0x" << std::hex << num1 << ") + "
          << std::dec << num2 << "(0x" << std::hex << num2 << ") = "
          << std::dec << result << "(0x" << std::hex << result << ")" << std::endl;



    return 0;
}

