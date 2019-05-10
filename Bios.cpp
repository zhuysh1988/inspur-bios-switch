#include "config.h"

#include "Bios.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <thread>

namespace inspur
{
namespace biosswitch
{
namespace bios
{
// using json = nlohmann::json;

std::string Bios::initBiosPresent()
{

    char cmd[16]="biostool.sh -p";
    char result[32]="";
    FILE* fp = NULL;
    std::string biosId = "1";
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
            biosId = boost::replace_all_copy(b_data[1], " ", "");
        }
    }
    return boost::replace_all_copy(biosId, "\n", "");;
}

bool Bios::getSwitchMod()
{
    bool switchMod = false;
    std::ifstream infile;
    infile.open("/etc/inspur-config/inspur-bios-switch", std::ios::in);
    char readinfo[4];
    while (!infile.eof())
    {
        infile >> readinfo;
    }
    infile.close();
    if (atoi(readinfo) == 1)
    {
        switchMod = true;
    }

    return switchMod;
}

bool Bios::autoSwitch(bool value)
{
    // 写文件
    int mode = value ? 1 :0;
    char cmd[64];
    sprintf(cmd, "echo %d > /etc/inspur-config/inspur-bios-switch", mode);
    int result = std::system(cmd);
    if (result)
    {
        std::fprintf(stderr, "set switch mod error! \n");
        value = !value;
    }

    return BiosObject::autoSwitch(value);
}

std::string Bios::runningIndex(std::string value)
{
    char cmd[64];
    sprintf(cmd, "biostool.sh -s");
    int result = std::system(cmd);
    if (result)
    {
        std::fprintf(stderr, "set bios error! \n");
    }

    return BiosObject::runningIndex(value);
}

// void Bios::monitorThread()
// {
//     bool biosMod = Bios::getSwitchMod();
//     if (biosMod)
//     {
//         std::cout << "Bios::monitor start ..." << std::endl;
//         int time = BiosObject::timeout();
//         int wait = 0;
//         bool powerOn = false;
//         while (wait <= time)
//         {
//             std::cout << "Bios::monitor start for : " << wait << std::endl;
//             biosMod = Bios::getSwitchMod();
//             if (!biosMod)
//             {
//                 break;
//             }
//             sleep(3);
//             wait += 3;
//             // IF POWER ON
//             if (powerOn)
//             {
//                 break;
//             } 
//         }
//         if (!powerOn)
//         {
//             BiosObject::isChanged(true);
//             BiosObject::runningIndex("1");
//             // reboot
//         }
//     }
// }

// void Bios::monitor()
// {
//     std::thread t (Bios::monitorThread);
//     t.join();
// }
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
