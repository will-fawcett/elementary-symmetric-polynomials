# elementary-symmetric-polynomials

A small C++ library for evaluating the [elementary symmetric polynomials](https://en.wikipedia.org/wiki/Elementary_symmetric_polynomial) (ESPs) of a set of values.

For inputs `x_1, ..., x_n`, the kth ESP is the sum of all products of `k` distinct inputs:

```
e_0 = 1
e_1 = x_1 + x_2 + ... + x_n
e_2 = x_1 x_2 + x_1 x_3 + ... + x_{n-1} x_n
...
e_n = x_1 x_2 ... x_n
```

## Usage

The library is two files: `esp.h` and `esp.cpp`. Drop them into your project and include the header.

```cpp
#include "esp.h"
#include <iostream>

int main() {
    ESPCalc calc({1.0, 2.0, 3.0, 4.0});

    // Evaluate a single e_k
    double e2 = calc.calc_esp_k(2);   // 1*2 + 1*3 + 1*4 + 2*3 + 2*4 + 3*4 = 35

    // Or evaluate e_0 ... e_n in one call
    std::vector<double> esps = calc.calc_esp_list();

    std::cout << "e_2 = " << e2 << "\n";
}
```

Build with any C++11 (or newer) compiler:

```
g++ -std=c++11 esp.cpp your_main.cpp -o esp_demo
```

## API

`ESPCalc(const std::vector<double>& roots)` — construct from the input values.

`double calc_esp_k(int k)` — return `e_k`. Defined for `0 <= k <= n`; throws `std::invalid_argument` otherwise.

`std::vector<double> calc_esp_list()` — return `[e_0, e_1, ..., e_n]` (length `n+1`).

`std::vector<std::vector<int>> calculate_indices(int size, int k)` — return the index combinations used internally to form `e_k`. For `k = 0` this is a single empty group (the empty product); for `k >= 1` it is all strictly-increasing `k`-tuples of indices into the input. Throws `std::invalid_argument` for `k < 0` or `k > size`. Results are cached on the instance.

## Notes

Index combinations are memoised per `k` on each `ESPCalc` instance and built iteratively, so repeated `calc_esp_k` calls reuse work and a `calc_esp_list` call computes each level once. The number of terms in `e_k` is `C(n, k)`, so evaluation cost grows combinatorially in `n`.
