#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#define MAX_TERM_SIZE 25

namespace {

typedef std::vector<std::pair<std::string, int> > StringToInt;

class CompareTerm {
 public:
  explicit CompareTerm(const std::string& term) : term_(term) { }

  bool operator()(const std::pair<std::string, int>& element) const {
    return element.first == term_;
  }
 private:
  std::string term_;
};

bool CompareCount(const std::pair<std::string, int>& lhs,
                  const std::pair<std::string, int>& rhs) {
  if (lhs.second == rhs.second) {
    // This seems pedantic, but it's good to be locale-aware when asked to sort
    // strings lexicographically.
    return std::lexicographical_compare(lhs.first.begin(), lhs.first.end(),
                                        rhs.first.begin(), rhs.first.end());
  }
  return lhs.second > rhs.second;
}

}  // end namespace

int main(int argc, const char* argv[]) {
  int N;
  std::cin >> N;

  char term_buffer[MAX_TERM_SIZE + 1];
  // This clears the newline from the reading of 'N'.
  std::cin.getline(term_buffer, MAX_TERM_SIZE);

  StringToInt term_to_count;
  term_to_count.reserve(N); 
  for (int i = 0; i < N; ++i) {
    std::cin.getline(term_buffer, MAX_TERM_SIZE);

    std::string term(term_buffer);

    // If the term is in the vector, increase the count. Else, add to the vector
    // with count = 1
    StringToInt::iterator it = std::find_if(term_to_count.begin(),
                                            term_to_count.end(),
                                            CompareTerm(term));
    if (it == term_to_count.end()) {
      // This could be insertion sort, but would require a resort on every count
      // increase.
      term_to_count.push_back(std::make_pair(term, 1));
    } else {
      ++it->second;
    }
  }

  size_t k;
  std::cin >> k;

  // The naive approach is to sort the whole vector by count and then read
  // the top three. However, this is O(n.log(n)) worst case. Instead, we can
  // just use partial sort for the top k in O(n.log(k)). As k << N this is
  // an optimization.
  /*
  // Naive approach:
  std::sort(term_to_count.begin(), term_to_count.end(), CompareCount);
  */

  std::partial_sort(term_to_count.begin(),
                    term_to_count.begin() + k,
                    term_to_count.end(),
                    CompareCount);

  for (size_t i = 0; i < k; ++i) {
    std::cout << term_to_count[i].first << "\n";
  }

  return 0;
}
