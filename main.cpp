#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <string>

int main()
{   
    ariel::Notebook work_book;
    std::cout<<std::endl<<"welcome to your notebook";
    std::cout<<std::endl<<"for write insert w";
    std::cout<<std::endl<<"for read insert r";
    std::cout<<std::endl<<"for erase insert e";
    std::cout<<std::endl<<"for show insert s";
    std::cout<<std::endl<<"for finish insert f:"<<std::endl;
    
    char func;
    std::cin>>func;

    // varibals for the functions 
        int page;
        int row;
        int colum;
        int temp_dir;
        int length;
        ariel::Direction dir;
        std::string word;

    //exexiut the func and get the next one
    while(func != 'f')
    {
        if(func == 'w'||func == 'r'||func == 'e')
        {
            std::cout<<std::endl<<"insert the page num:"<<std::endl;
            std::cin>>page;

            std::cout<<std::endl<<"insert the row num:"<<std::endl;
            std::cin>>row;

            std::cout<<std::endl<<"insert the colum num:"<<std::endl;
            std::cin>>colum;

            std::cout<<std::endl<<"insert the direction:"<<std::endl<<"for Horizontal insert 0"<<std::endl<<"for Vertical insert 1"<<std::endl;
            std::cin>>temp_dir;
            if(temp_dir==0)
            {
                dir= ariel::Direction::Horizontal;
            }
            else
            {
                dir= ariel::Direction::Vertical;
            }
            //for write:
            if(func == 'w')
            {
                std::cout<<std::endl<<"insert what you want to write max 100:"<<std::endl;
                std::cin>>word;
                work_book.write(page,row,colum,dir,word);
            }
            if(func == 'r')
            {
                std::cout<<std::endl<<"insert the length of what you want to read:"<<std::endl;
                std::cin>>length;
                std::cout<<std::endl<<work_book.read(page,row,colum,dir,length);

            }
            if(func == 'e')
            {
                std::cout<<std::endl<<"insert the length of what you want to erase:"<<std::endl;
                std::cin>>length;
                work_book.erase(page,row,colum,dir,length);

            }
        }
        if(func == 's')
        {
            std::cout<<std::endl<<"insert the page num:"<<std::endl;
            std::cin>>page;

            work_book.show(page);
        }
        //next action
        std::cout<<std::endl<<"for write insert w:";
        std::cout<<std::endl<<"for read insert r:";
        std::cout<<std::endl<<"for erase insert e:";
        std::cout<<std::endl<<"for show insert s:";
        std::cout<<std::endl<<"for finish insert f:"<<std::endl;
        std::cin>>func;
    
    }
    return 0;
}
