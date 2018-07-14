#include <iostream>
#include <string>
#include "ArrayList.hpp"
#include "OutOfBoundsException.hpp"

int main()

{

  try
    {
      std::cout << "Enter 10 student IDs and names: ";

      ArrayList<std::string> list;

      for (int i = 0; i < 10; ++i)
        {
          std::string IDandName;
          std::getline(std::cin, IDandName);
          list.add(IDandName);
        }
      
      for (int i = 0; i < 10; ++i)
        {
          std::string temp = list.at(i);

          std::string ID = "";
          int j = 0;
          for (; temp[j]!= ' '; ++j)
            ID += temp[j];

          for (; j < temp.size(); ++j)
            std::cout << temp[j];

          std::cout << " (ID#" << ID << ")" << std::endl;
       
         
        }
    }
  catch (OutOfBoundsException e)
    {
      std::cout << "out of bounds" << std::endl;
    }

    return 0;
}

