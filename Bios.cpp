#include "config.h"

#include "Bios.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

namespace inspur
{
namespace biosswitch
{
namespace bios
{
// using json = nlohmann::json;

void Bios::initBiosPresent()
{
    char cmd[16]="biostool.sh -p";
    char result[32]="";
    FILE* fp = NULL;
    if ((fp = popen(cmd, "r")) != NULL)
    {
        fread(result, 1, sizeof(result) - 1, fp);
        std::string temp = result;
        std::string::size_type idx;
        idx= temp.find(":");
        if (idx != std::string::npos)
        {
            std::vector<std::string> b_data;
            boost::split(b_data, result, boost::is_any_of(":"));
            std::string biosId = boost::replace_all_copy(b_data[1], " ", "");
            BiosObject::runningIndex(biosId);
        }

    }
}

// uint32_t runningIndex(uint32_t value)
// {
//     return BiosObject::runningIndex;
// }

// uint32_t timeOut(uint32_t value)
// {
//     return BiosObject::timeOut;
// }
// void Bios::restore()
// {

// }
} // namespace dimm
} // namespace assets
} // namespace inspur
