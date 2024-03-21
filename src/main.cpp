#include <fstream>
#include <iostream>
#include <filesystem>
#include <iterator>


int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  auto path  = std::filesystem::current_path() / argv[1];
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    std::cerr << "Failed to open " << path << '\n';
    return 1;
  }

  char c;
  while (file.get(c)) {
    std::cout << std::hex << (uint16_t)c << std::endl;
  }

  return 0;
}
