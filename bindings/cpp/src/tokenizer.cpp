#include "tokenizer/tokenizer.hpp"

#include <cassert>
#include <cstring>
#include <exception>
#include <vector>

#include "tokenizers.h"

#define NO_ERROR 0

namespace tokenizers {

Tokenizer::~Tokenizer() {
  if (tokenizer_c_ptr != nullptr) {
    tokenizer_free(tokenizer_c_ptr);
  }
}

void Tokenizer::from_pretrained(const std::string& identifier) {
  assert(tokenizer_c_ptr == nullptr);
  int error = tokenizer_from_pretrained(identifier.c_str(), &tokenizer_c_ptr);
  if (error != NO_ERROR || tokenizer_c_ptr == nullptr) {
    throw std::runtime_error("Tokenizer from pretrained failed whit code: " +
                             std::to_string(error));
  }
}

Encoding Tokenizer::encode(const std::string& input) {
  if (tokenizer_c_ptr == nullptr) {
    throw std::runtime_error("Tokenizer not initialized");
  }

  if (input.empty()) {
    throw std::runtime_error("Empty is input");
  }

  void* encoding_c_ptr = nullptr;
  int error = tokenizer_encode(input.c_str(), tokenizer_c_ptr, &encoding_c_ptr);
  if (error != NO_ERROR || encoding_c_ptr == nullptr) {
    throw std::runtime_error("Tokenizer encode failed whit code: " + std::to_string(error));
  }

  const uint32_t* out_ptr = nullptr;
  uintptr_t out_len = 0;

  error = tokenizer_encoding_get_ids(encoding_c_ptr, &out_ptr, &out_len);
  if (error != NO_ERROR || out_ptr == nullptr) {
    throw std::runtime_error("Encode get ids failed whit code: " + std::to_string(error));
  }

  Encoding encoding;
  encoding.ids.resize(out_len);
  std::memcpy(encoding.ids.data(), out_ptr, out_len);

  tokenizer_encoding_free(encoding_c_ptr);

  return std::move(encoding);
}

}  // namespace tokenizers