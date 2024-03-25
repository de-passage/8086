#include <cstdint>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iterator>

using opcode_handler = bool (*)(std::basic_istream<char>& source, char first_byte);

constexpr static inline uint8_t MOV_OPCODE = 0b100010;
enum class mod_type {
  mem_no_displacement = 0b00,
  mem_8_bit_displacement = 0b01,
  mem_16_bit_displacement = 0b10,
  reg = 0b11
};

enum class reg_wide {
  AX = 0b000,
  CX = 0b001,
  DX = 0b010,
  BX = 0b011,
  SP = 0b100,
  BP = 0b101,
  SI = 0b110,
  DI = 0b111
};

template<typename... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os, reg_wide reg) {
  switch (reg) {
    case reg_wide::AX: os << "ax"; break;
    case reg_wide::CX: os << "cx"; break;
    case reg_wide::DX: os << "dx"; break;
    case reg_wide::BX: os << "bx"; break;
    case reg_wide::SP: os << "sp"; break;
    case reg_wide::BP: os << "bp"; break;
    case reg_wide::SI: os << "si"; break;
    case reg_wide::DI: os << "di"; break;
  }
  return os;
}

enum class reg_narrow {
  AL = 0b000,
  CL = 0b001,
  DL = 0b010,
  BL = 0b011,
  AH = 0b100,
  CH = 0b101,
  DH = 0b110,
  BH = 0b111
};

template<typename... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& out, reg_narrow reg) {
  switch (reg) {
    case reg_narrow::AL: out << "al"; break;
    case reg_narrow::CL: out << "cl"; break;
    case reg_narrow::DL: out << "dl"; break;
    case reg_narrow::BL: out << "bl"; break;
    case reg_narrow::AH: out << "ah"; break;
    case reg_narrow::CH: out << "ch"; break;
    case reg_narrow::DH: out << "dh"; break;
    case reg_narrow::BH: out << "bh"; break;
  }
  return out;
}

void print_register(std::basic_ostream<char>& out, uint8_t reg, bool wide) {
  if (wide) {
    out << reg_wide(reg);
  } else {
    out << reg_narrow(reg);
  }
}

bool decode_mov(std::basic_istream<char>& source, char first_byte) {
  char second_byte;
  if (!source.get(second_byte)) {
    return false;
  }
  bool destination = (first_byte & 0b10) != 0;
  bool wide = (first_byte & 0b1) != 0;
  mod_type mod = (mod_type)((second_byte & 0b11000000) >> 6);
  uint8_t reg = (second_byte & 0b111000) >> 3;
  uint8_t rm = second_byte & 0b111;

  if (mod != mod_type::reg) {
    std::cerr << "unsupported mod value: " << std::hex << (int)mod << '\n';
    return false;
  }

  std::cout << "mov ";
  if (destination) {
    print_register(std::cout, reg, wide);
  } else {
    print_register(std::cout, rm, wide);
  }
  std::cout << ", ";
  if (destination) {
    print_register(std::cout, rm, wide);
  } else {
    print_register(std::cout, reg, wide);
  }

  return true;
}


template<typename T, typename ...Ts>
void print_binary(std::basic_ostream<Ts...>& out, T value) {
  for (int i = sizeof(T) * 8 - 1; i >= 0; --i) {
    out << ((value >> i) & 1);
  }
}

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

  std::cout << "bits 16\n\n";

  char c;
  while (file.get(c)) {
    uint8_t opcode = (c & 0b11111100) >> 2;
    print_binary(std::cerr, opcode); std::cerr << '\n';
    if (opcode == MOV_OPCODE) {
      decode_mov(file, c);
    } else {
      std::cerr << "Unknown opcode: " << std::hex << (uint16_t)opcode << '\n';
    }

    std::cout << '\n';
  }

  return 0;
}
