#pragma once

#include "sha1_utils.hpp"

#include <array>
#include <fstream>
#include <string>
#include <string_view>

namespace okon {
class splitted_files
{
public:
  explicit splitted_files(std::string_view path,
                          std::ios::openmode mode = std::ios::in | std::ios::out)
  {
    auto name = std::string{ "00" };

    for (auto& output_file : m_files) {
      output_file.open(path.data() + name, mode);

      if (name[1] == '9') {
        name[1] = 'A';
      } else if (name[1] == 'F') {
        name[1] = '0';

        if (name[0] == '9') {
          name[0] = 'A';
        } else {
          ++name[0];
        }
      } else {
        ++name[1];
      }
    }
  }

  std::fstream& sha1_file(std::string_view sha1)
  {
    const auto file_index = chars_to_byte(sha1.data());
    return m_files[file_index];
  }

  std::fstream& operator[](unsigned index)
  {
    return m_files[index];
  }

  auto begin()
  {
    return std::begin(m_files);
  }

  auto end()
  {
    return std::end(m_files);
  }

private:
  std::array<std::fstream, 256u> m_files;
};
}