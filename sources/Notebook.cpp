#include "Direction.hpp"
#include <string>
#include "Notebook.hpp"
#include <unordered_map>
#include <vector>

namespace ariel{
    void Notebook::write(int page,int row, int colum, ariel::Direction dir, const std::string &word)
    {
        //check contain ~
        if(word.find('~')!=std::string::npos)
        {
            throw std::invalid_argument("can wrote ~");
        }
        //check negtive numbers
        if(page<0||row<0||colum<0)
        {
            throw std::invalid_argument("bad input can get negetive numbers");
        }
        // check not to big colum
        if(colum>maxcolum)
        {
            throw std::invalid_argument("cant insert in to this colum");
        }
        //check to what dir you want to write
        if(dir == ariel::Direction::Horizontal)
        {
            write_Horizontal(page,row,colum,word);
        }
        else{
            write_Vertical(page,row,colum,word);
        }
    }

    void Notebook::write_Horizontal(int page, int row, int colum, const std::string &word)
    {
        if(colum+word.length()-1>maxcolum)
        {
            throw std::invalid_argument("cant insert in to this colum");
        }
        //check can write
        if(My_book.find(page) == My_book.end())
        {
            std::unordered_map<int,std::vector<char>> temp;
            My_book[page] = temp;
            My_book[page][row] = std::vector<char>(100,'_');
        }
        else
        {
            if(My_book[page].find(row) == My_book[page].end())
            {
                My_book[page][row] = std::vector<char>(100,'_');
            }
            else
            {
                for(int curr = 0; curr < word.length(); curr++)
                {
                    if(My_book[page][row][colum+curr]!= '_')
                    {
                        throw std::invalid_argument("you cant write here this place is writen");
                    }
                }
            }
        }
        //if can
        for(int curr = 0; curr <= word.length(); curr++)
        {
            My_book[page][row][colum+curr] = word[curr];
        } 
    }

    void Notebook::write_Vertical(int page, int row, int colum, const std::string &word)
    {
        if(My_book.find(page) == My_book.end())
        {
            std::unordered_map<int,std::vector<char>> temp;
            My_book[page] = temp;
            for(int curr=0;curr<word.length();curr++)
            {
                My_book[page][row] = std::vector<char>(100,'_');
            }
        }
        else
        {
            for(int curr=0;curr<word.length();curr++)
            {
                if(My_book[page].find(row+curr) == My_book[page].end())
                {
                    My_book[page][row+curr] = std::vector<char>(100,'_');
                }
                else
                {
                    if(My_book[page][row][colum]!= '_')
                    {
                        throw std::invalid_argument("you cant write here this place is writen");
                    }
                }
            }
        }

        //if can
        for(int curr = 0; curr <= word.length(); curr++)
        {
            My_book[page][row+curr][colum] = word[curr];
        } 
    }
    
    std::string Notebook::read(int page,int row, int colum, ariel::Direction dir, int length)
    {
        //check negtive numbers
        if(page<0||row<0||colum<0)
        {
            throw std::invalid_argument("bad input can get negetive numbers");
        }
        // check not to big colum
        if(colum>maxcolum)
        {
            throw std::invalid_argument("cant read in to this colum");
        }
        //check to what dir you want to write
        if(dir == ariel::Direction::Horizontal)
        {
            return read_Horizontal(page,row,colum,length);
        }
        else{
            return read_Vertical(page,row,colum,length);
        }
    }

    std::string Notebook::read_Horizontal(int page, int row, int colum, int length)
    {
        std::string ans = "";
        if(colum+length-1>maxcolum)
        {
            throw std::invalid_argument("cant read from this colum");
        }
        //check not null page
        if(My_book.find(page) == My_book.end())
        {
            for(int i=0;i<length;i++)
            {
                ans = ans+"_";
            }
            return ans;
        }

        //check have row
        if(My_book[page].find(row) == My_book[page].end())
        {
            for(int i=0;i<length;i++)
            {
                ans = ans+"_";
            }
            return ans;
        }
        //read the row
        for(int curr = 0; curr < length; curr++)
        {
            ans = ans + My_book[page][row][colum+curr];
        }
        return ans;
    }

    std::string Notebook::read_Vertical(int page, int row, int colum, int length)
    {
        std::string ans = "";
        //check not null page
        if(My_book.find(page) == My_book.end())
        {
            for(int i=0;i<length;i++)
            {
                ans = ans+"_";
            }
            return ans;
        }

        //check have row if do not read from it if no write _
        for(int curr = 0; curr < length; curr++)
        {
            if(My_book[page].find(row+curr) == My_book[page].end())
            {
                ans = ans+"_";
            }
            else
            {
                 ans = ans + My_book[page][row+curr][colum];
            }
        }
        return ans;
    }

    void Notebook::erase(int page, int row, int colum, ariel::Direction dir, int length)
    {
//check negtive numbers
        if(page<0||row<0||colum<0)
        {
            throw std::invalid_argument("bad input can get negetive numbers");
        }
        // check not to big colum
        if(colum>maxcolum)
        {
            throw std::invalid_argument("cant remove in to this colum");
        }
        //check to what dir you want to write
        if(dir == ariel::Direction::Horizontal)
        {
            erase_Horizontal(page,row,colum,length);
        }
        else{
            erase_Vertical(page,row,colum,length);
        }
    }
    
    void Notebook::erase_Horizontal(int page, int row, int colum, int length)
    {
        if(colum+length-1>maxcolum)
        {
            throw std::invalid_argument("cant remove from this colum");
        }

        if(My_book.find(page) == My_book.end())
        {
            std::unordered_map<int,std::vector<char>> temp;
            My_book[page] = temp;
        }
        if(My_book[page].find(row) == My_book[page].end())
        {
            My_book[page][row] = std::vector<char>(100,'_');
        }
        for(int curr = 0; curr < length; curr++)
        {
            My_book[page][row][colum+curr] = '~';
        }
    }
    
    void Notebook::erase_Vertical(int page, int row, int colum, int length)
    {
        if(My_book.find(page) == My_book.end())
        {
            std::unordered_map<int,std::vector<char>> temp;
            My_book[page] = temp;
        }
        for(int curr = 0; curr < length; curr++)
        {
            if(My_book[page].find(row+curr) == My_book[page].end())
            {
                My_book[page][row] = std::vector<char>(100,'_');
            }
            My_book[page][row][colum+curr] = '~';
        } 

    }
    void Notebook::show(int page)
    {

    }
}


