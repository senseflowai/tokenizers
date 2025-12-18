<p align="center">
  <br>
  <img src="https://huggingface.co/landing/assets/tokenizers/tokenizers-logo.png" width="600"/>
  <br>
<p>
<p align="center">
  <a href="https://github.com/huggingface/tokenizers/blob/master/LICENSE">
    <img alt="GitHub" src="https://img.shields.io/github/license/huggingface/tokenizers.svg?color=blue">
  </a>
</p>
<br>

C++ implementation of today's most used tokenizers, with a focus on performance and
versatility. Bindings over the [Rust](https://github.com/huggingface/tokenizers/tree/master/tokenizers) implementation.

## Installation

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Basic example

```c++
#include "tokenizer/tokenizer.hpp"
...
tokenizers::Tokenizer tokenizer;
tokenizer.from_pretrained("google/siglip2-base-patch16-224");
auto encoding = tokenizer.encode("Hello world!");
...
```

## License

[Apache License 2.0](../../LICENSE)