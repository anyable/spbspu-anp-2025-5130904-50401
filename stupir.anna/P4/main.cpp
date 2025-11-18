#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip> 
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
  while (max_mem_now)
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
  mem[lenght] = '\0'; ////////////////////
  size = lenght;
  if (is_skipws)
  {
    input >> std::skipws;
  }
  return mem;
}

int main()
{
  char * mem = nullptr;
  size_t size = 0;
  mem = getLine(std::cin, size);
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
}
