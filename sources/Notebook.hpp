#include "Direction.hpp"
#include <string>
#include <vector>

namespace ariel{
    class Notebook{
        private:
            const int maxcolum = 100;
            std::vector<std::vector<std::vector<char>>> arr_book;
        public:
            void write(int page, int row, int colum, ariel::Direction dir, const std::string &word);
            std::string static read(int page, int row, int colum, ariel::Direction dir, int length);
            void erase(int page, int row, int colum, ariel::Direction dir, int length);
            void show(int page);
    };
}
