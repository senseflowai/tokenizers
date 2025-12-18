#ifndef TOKENIZER_HPP_
#define TOKENIZER_HPP_

#include <cstdint>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#ifdef TOKENIZER_EXPORTS
#define TOKENIZER_API __declspec(dllexport)
#else
#define TOKENIZER_API __declspec(dllimport)
#endif
#else
#define TOKENIZER_API __attribute__((visibility("default")))
#endif

#include <string>

namespace tokenizers {

/**
 * @brief Allocator for internal resources
 * @class Allocator
 */
template <class T>
class TOKENIZER_API Allocator : public std::allocator<T> {
 public:
  Allocator() = default;
  ~Allocator() = default;
};

/**
 * @struct Encoding
 */
struct Encoding {
  std::vector<uint32_t> ids;
};

/**
 * @brief Main Tokenizer class
 * @class Tokenizer
 */
class TOKENIZER_API Tokenizer {
 public:
  Tokenizer() = default;
  ~Tokenizer();

  /**
   * @brief load from huggingface repository
   * @param identifier path to repository
   */
  void from_pretrained(const std::string& identifier);

  /**
   * @brief tokenize input text
   * @param input input string
   */
  Encoding encode(const std::string& input);

 private:
  void* tokenizer_c_ptr = nullptr;
};
}  // namespace tokenizers

#endif
