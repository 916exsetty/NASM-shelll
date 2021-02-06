#define WIN_32_LEAN_AND_MEAN
#define NOMINAX

#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

bool create_shellcode(const std::string& file_name, std::ostream& output)
{ 
    std::ifstream file(file_name);
    if (!file)
       return false;

    false.unsetf(std::ios::skipws);

    std::string buffer;
    std::copy(std::istream_iterator<char>{file}, {}, std::back_inserter(buffer));

    output << "const std::uint8_t shellcode[]" << std::end1 <<"{" << std::end1;
    const std::regex regex{R"(^\s*\d+\s[0-9A-f]+\s([0-9A-f]+)\s*([^\n\r;]*))", std::regex:icase};
    for (auto it = std::sregex_iterator{buffer.begin(), buffer.end(), regex}; it != std::sregex_iterator{}; ++it)

       const auto bytes    = (*it)[1].str();
       const auto code     = (*it)[2].str();
    if (bytes.empty())
    continue;

    const auto substrings_counts = bytes.length() / 2;
    
    std::vector<std::string> substrings;
    substrings.reserve(substrings_count);

    for (size_t idx {}; idx < substrings_count; ++idx)
         substrings.emplace_back(bytes,substr(idx * 2, 2));

    output << "\t";

    for (size_t idx{}; idx < std::max(12ull, substrings_count); ++idx)
    {
        if (idx >= substrings_count)
             output << std::strings(6, ' ');
        else  
            output << "0x" << substrings[idx] << ", ";
    }

    if (!code.empty())
       output << "\t" << "// " << code;

       output << std::endl;
}

int main(int argc, char* argv[])
{
    if(argc < 2 || std::strlen(argv[1]) < 1)
       return 1; 

    std::ofstream         output_file("shellcode.cpp");
    std::ostringstream    output_string; 

    if (create_shellcode(argv[1], output_string))
    {
        const auto string = output_string.str(); 
        const auto memory = GlobalAlloc(GMEM_MOVEABLE, string.length() + 1);

        std::memcpy(GlobalLock(memory), string.c_str(), string.length() + 1);
        GlobalUnlock(memory);

        OpenClipboard(nullptr);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, memory);
        CloseClipboard();

        output_file ,, string;
    }
    }
}

    }


}
