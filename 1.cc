#include <iostream>
#include <list>
#include <string>
#include <vector>

#define MAX_CMD_SIZE (4)

namespace {

class RingBuffer {
 public:
  explicit RingBuffer(size_t size) : size_(size) { }

  void Add(const std::string& s) {
    if (buffer_.size() == size_)
      RemoveOldest();
    buffer_.push_back(s);
  }

  void RemoveOldest() {
    buffer_.pop_front();
  }

  void List() const {
    for (std::list<std::string>::const_iterator it = buffer_.begin();
         it != buffer_.end(); ++it) {
      std::cout << *it << "\n";
    }
  }

 private:
  size_t size_;
  std::list<std::string> buffer_;
};

}  // end namespace

int main(int argc, const char* argv[]) {
  int N;
  std::cin >> N;

  RingBuffer buffer(N);

  for (;;) {
    char cmd;
    std::cin >> cmd;
    switch (cmd) {
      case 'A': {
          int count;
          std::cin >> count;

          char str_buffer[32];
          // get to the start of the next line.
          std::cin.getline(str_buffer, 31);
          for (int i = 0; i < count; ++i) {
            std::cin.getline(str_buffer, 31);
            buffer.Add(std::string(str_buffer));
          }
        }
        break;

      case 'R': {
          int count;
          std::cin >> count;
          for (int i = 0; i < count; ++i) {
            buffer.RemoveOldest();
          }
        }
        break;

      case 'L':
        buffer.List();
        break;

      case 'Q':
        return 0;

      default:
        break;
    }
  }

  return 0;
}
