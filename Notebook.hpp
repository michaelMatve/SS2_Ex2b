#include "Direction.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace ariel{
    class Notebook{
        private:
            static const int maxcolum = 99;
            std::unordered_map<int, std::unordered_map<int,std::vector<char>>>My_book;

            void write_Horizontal(int page, int row, int colum, const std::string &word);
            void write_Vertical(int page, int row, int colum, const std::string &word);
            std::string read_Horizontal(int page, int row, int colum, int length);
            std::string read_Vertical(int page, int row, int colum, int length);
            void erase_Horizontal(int page, int row, int colum, int length);
            void erase_Vertical(int page, int row, int colum, int length);
        public:
            void write(int page, int row, int colum, ariel::Direction dir, const std::string &word);
            std::string read(int page, int row, int colum, ariel::Direction dir, int length);
            void erase(int page, int row, int colum, ariel::Direction dir, int length);
            void show(int page);
    };
}
