#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[]) {
  int N;
  std::cin >> N;

  // The trick here is to store each element in its slot and the total product,
  // then iterate through the array and divide the total product by the value in
  // the slot. O(N) guaranteed and no extra space used.
  std::vector<int64_t> arr;
  arr.reserve(N);

  int num_zeroes = 0;
  int64_t product = 1;
  for (int i = 0; i < N; ++i) {
    int64_t value;
    std::cin >> value;
    // if the value is 0, then all elements except this one are 0. If more than
    // one element is 0 then all elements are 0.
    if (value == 0)
      ++num_zeroes;
    else
      product *= value;
    arr.push_back(value);
  }

  // If more than one element is 0 then all elements are 0. If only one element
  // is zero, then that should be the total product (without the 0 taken into
  // account) and the others should all be 0. Otherwise, just divide as
  // expected.
  switch (num_zeroes) {
    case 0:
      for (int i = 0; i < N; ++i) {
          std::cout << product / arr[i] << "\n";
      }
      break;

    case 1:
      for (int i = 0; i < N; ++i) {
        if (arr[i] == 0)
          std::cout << product << "\n";
        else
          std::cout << "0\n";
      }
      break;

    default:
      for (int i = 0; i < N; ++i) {
        std::cout << "0\n";
      }
  }

  return 0;
}
