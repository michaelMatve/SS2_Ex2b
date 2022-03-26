#include "Direction.hpp"
#include <string>
#include <iostream>
#include "Notebook.hpp"
#include <unordered_map>
#include <stdexcept>
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

        if(colum+int(word.length())-1>maxcolum)
        {
            throw std::invalid_argument("cant insert in to this colum");
        }
        //check if this page olredy exist
        if(My_book.find(page) == My_book.end())
        {
            std::unordered_map<int,std::vector<char>> temp;
            My_book[page] = temp;
        }

        //check if row exist
        if(My_book[page].find(row) == My_book[page].end())
        {
            My_book[page][row] = std::vector<char>(maxcolum+1,'_');
        }

        //check can write if not throw
        for(int curr = 0; curr < word.length(); curr++)
        {
            if(My_book[page][row][uint(colum+curr)]!= '_')
            {
                throw std::invalid_argument("you cant write here this place is writen");
            }
        }
        
        //if can
        for(int curr = 0; curr <= word.length(); curr++)
        {
            My_book[page][row][uint(colum+curr)] = word[uint(curr)];
        } 
    }

    void Notebook::write_Vertical(int page, int row, int colum, const std::string &word)
    {
        if(My_book.find(page) == My_book.end())
        {
            std::unordered_map<int,std::vector<char>> temp;
            My_book[page] = temp;
        }
        for(int curr=0;curr<word.length();curr++)
        {
            if(My_book[page].find(row+curr) == My_book[page].end())
            {
                My_book[page][row+curr] = std::vector<char>(maxcolum+1,'_');
                My_book[page][row+curr][uint(colum)] = word[uint(curr)];
            }
            else
            {
                if(My_book[page][row][uint(colum)]!= '_')
                {
                    throw std::invalid_argument("you cant write here this place is writen");
                }
                My_book[page][row+curr][uint(colum)] = word[uint(curr)];
            }
        }
    }
    
    std::string Notebook::read(int page,int row, int colum, ariel::Direction dir, int length)
    {
        //check negtive numbers
        if(page<0||row<0||colum<0||length<1)
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
        return read_Vertical(page,row,colum,length);
    }

    std::string Notebook::read_Horizontal(int page, int row, int colum, int length)
    {
        std::string ans;
        if(colum+length-1>maxcolum)
        {
            throw std::invalid_argument("cant read from this colum");
        }
        //check not null page
        if(My_book.find(page) == My_book.end())
        {
            for(int i=0;i<length;i++)
            {
                ans +="_";
            }
            return ans;
        }

        //check have row
        if(My_book[page].find(row) == My_book[page].end())
        {
            for(int i=0;i<length;i++)
            {
                ans +="_";
            }
            return ans;
        }
        //read the row
        for(int curr = 0; curr < length; curr++)
        {
            ans += My_book[page][row][uint(colum+curr)];
        }
        return ans;
    }

    std::string Notebook::read_Vertical(int page, int row, int colum, int length)
    {
        std::string ans;
        //check not null page
        if(My_book.find(page) == My_book.end())
        {
            for(int i=0;i<length;i++)
            {
                ans +="_";
            }
            return ans;
        }

        //check have row if do not read from it if no write _
        for(int curr = 0; curr < length; curr++)
        {
            if(My_book[page].find(row+curr) == My_book[page].end())
            {
                ans +="_";
            }
            else
            {
                 ans += My_book[page][row+curr][uint(colum)];
            }
        }
        return ans;
    }

    void Notebook::erase(int page, int row, int colum, ariel::Direction dir, int length)
    {
        //check negtive numbers
        if(page<0||row<0||colum<0||length<1)
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
            My_book[page][row] = std::vector<char>(maxcolum+1,'_');
        }
        for(int curr = 0; curr < length; curr++)
        {
            My_book[page][row][uint(colum+curr)] = '~';
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
                My_book[page][row+curr] = std::vector<char>(maxcolum+1,'_');
            }
            My_book[page][row+curr][uint(colum)] = '~';
        } 

    }
    
    void Notebook::show(int page)
    {
        const int start_row_showed = 10;
        //firest we show 10 row then we ask the user how many more rows to show
        int num_rows = start_row_showed;
        int curr_row = 0;
        while (num_rows >0)
        {
            for(int curr=0;curr<num_rows;curr++)
            {
                std::cout<< curr_row <<" : "<<read(page,curr_row,0,ariel::Direction::Horizontal,maxcolum+1)<< std::endl;
                curr_row++;
            }
            std::cout<< "insert the numbers of more row you want to see:"<<std::endl<< "for exit put 0";
            std::cin>>num_rows;
        }
    }
}


