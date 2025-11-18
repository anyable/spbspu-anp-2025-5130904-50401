#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip> 
namespace stupir
{
  void copy(const char * mem_old, size_t old, char * mem_new)
  {
    for (size_t i = 0; i < old; ++i)
    {
      mem_new[i] = mem_old[i];
    }
  }

  char * give_memory(char * mem_old, size_t & max_mem_now)
  {
    size_t old_max_mem = max_mem_now;
    max_mem_now *= 2;
    char * mem_new = nullptr;
    while (max_mem_now > old_max_mem)
    {
      mem_new = reinterpret_cast< char * >(malloc(sizeof(char) * max_mem_now));
      if (mem_new != nullptr)
      {
        copy(mem_old, old_max_mem, mem_new);
        free(mem_old);
        return mem_new;
      }
      max_mem_now--;
    }
    free(mem_old);
    return nullptr;
  }

  char * get_line(std::istream & input, size_t & size)
  {
    bool is_skipws = input.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      input >> std::noskipws;
    }
    char a = '\0';
    input >> a;
    if (!input || a == '\n')
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
    while (input >> a && a != '\n')
    {
      if (lenght > max_mem_now - 1)
      {
        char * mem_extend = give_memory(mem, max_mem_now);
        if (mem_extend == nullptr)
        {
          return nullptr;
        }
        mem = mem_extend;
      }
      mem[lenght] = a;
      lenght++;
    }
    if (!input)
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

  size_t compare_unic(const char * line1, const char * line2, size_t len1, size_t len2)
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

  size_t count_num(const char * line, size_t len)
  {
    size_t result = 0;
    for (size_t i = 0; i < len; ++i)
    {
      result += std::isdigit(line[i]);
    }
    return result;
  }

  char * add_num(char * start, const char * line1, size_t len1, const char * line2, size_t len2, size_t len_start)
  {
    copy(line1, len1, start);
    size_t j = 0;
    for (size_t i = len1; i < len_start; ++i)
    {
      for (; j < len2; ++j)
      {
        if (std::isdigit(line2[j]))
        {
          start[i] = line2[j];
          j++;
          break;
        }
      }
    }
    start[len1 + len2] = '\0';
    return start;
  }
}
int main()
{
  namespace stu = stupir;
  char * mem = nullptr;
  size_t size = 0;
  mem = stu::get_line(std::cin, size);
  if (size == 0)
  {
    std::cerr << '\n' << "Invalid string\n";
    return 2;
  }
  if (mem == nullptr)
  {
    std::cerr << "Failed to allocate memory for a row\n";
    return 1;
  }
  size_t task1 = 0;
  const char * line1 = "abs";
  size_t size_line1 = 3;
  task1 = stu::compare_unic(mem, line1, size, size_line1);

  const char * line2 = "g1h2k";
  size_t size_line2 = 5;
  size_t count_num_line2 = stu::count_num(line2, size_line2);
  if (count_num_line2 == 0)
  {
    std::cout << task1 << '\n' << mem << '\n';
    free(mem);
    return 0;
  }
  size_t len_new_line = size + count_num_line2 + 1;
  char * buffer = reinterpret_cast< char * >(malloc(sizeof(char) * len_new_line));
  if (buffer == nullptr)
  {
    free(mem);
    std::cerr << "Failed to place a new line in dynamic memory\n";
    return 1;
  }
  char * task2 = stu::add_num(buffer, mem, size, line2, size_line2, len_new_line);
  std::cout << task1 << '\n';
  std::cout << task2 << '\n';
  free(mem);
  free(task2);
}
