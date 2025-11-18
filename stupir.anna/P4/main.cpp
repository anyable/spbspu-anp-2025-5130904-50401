#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip> 
namespace stupir
{
  char * giveMemory(char * mem_old, size_t & max_mem_now)
  {
    size_t old_max_mem = max_mem_now;
    max_mem_now *= 2;
    char * mem_new = nullptr;
    while (max_mem_now > old_max_mem)
    {
      mem_new = reinterpret_cast< char * >(realloc(mem_old, max_mem_now));
      if (mem_new != nullptr)
      {
        mem_old = mem_new;
        break;
      }
      max_mem_now--;
    }
    return mem_old;
  }

  char * getLine(std::istream & input, size_t & size)
  {
    bool is_skipws = input.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      input >> std::noskipws;
    }
    char a = '\0';
    input >> a;
    if (!input)
    {
      size = 0;
      return nullptr;
    }
    size_t lenght = 1;
    size = lenght;
    size_t max_mem_now = 10;
    char * mem = nullptr;
    while (max_mem_now > 1)
    {
      mem = reinterpret_cast< char * >(malloc(sizeof(char) * max_mem_now));
      if (mem != nullptr)
      {
        break;
      }
      max_mem_now--;
    }
    if (mem == nullptr)
    {
      return nullptr;
    }
    mem[0] = a;
    while (input >> a)
    {
      if (lenght > max_mem_now - 1)
      {
        char * mem_extend = giveMemory(mem, max_mem_now);
        if (mem_extend == nullptr)
        {
          free(mem);
          return nullptr;
        }
        mem = mem_extend;
      }
      mem[lenght] = a;
      lenght++;
    }
    if (!input.eof())
    {
      size = 0;
      free(mem);
      return nullptr;
    }
    mem[lenght] = '\0'; 
    size = lenght;
    if (is_skipws)
    {
      input >> std::skipws;
    }
    return mem;
  }

  size_t compareUnic(const char * line1, const char * line2, size_t len1, size_t len2)
  {
    if (len1 > len2)
    {
      for (size_t i = 0; i < len1; ++i)
      {
        char t = line1[i];
        for (size_t j = 0; j < len2; ++j)
        {
          if (t == line2[j])
          {
            return 1;
          }
        }
      }
    }
    else
    {
      for (size_t i = 0; i < len2; ++i)
      {
        char t = line2[i];
        for (size_t j = 0; j < len1; ++j)
        {
          if (t == line1[j])
          {
            return 1;
          }
        }
      }
    }
    return 0;
  }
}


int main()
{
  namespace stu = stupir;
  char * mem = nullptr;
  size_t size = 0;
  mem = stu::getLine(std::cin, size);
  if (size == 0)
  {
    std::cerr << "Invalid string\n";
    return 2;
  }
  if (mem == nullptr)
  {
    std::cerr << "Failed to allocate memory for a row\n";
    return 1;
  }
  size_t task1 = 0;
  const char * line_compare = "abs";
  size_t size_line_compare = 3;
  task1 = stu::compareUnic(mem, line_compare, size, size_line_compare);

  
  free(mem);
  std::cout << task1 << '\n';
}
 