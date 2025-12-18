#include <iostream>
#include <ostream>

#include "tokenizer/tokenizer.hpp"

int main(int argc, char* argv[]) {
  try {
    tokenizers::Tokenizer tokenizer;
    tokenizer.from_pretrained("google/siglip2-base-patch16-224");
    auto encoding = tokenizer.encode("Hello world!");
    std::cout << "encoded ids: [";
    for (auto id : encoding.ids) {
      std::cout << id << ',';
    }
    std::cout << ']' << std::endl;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}