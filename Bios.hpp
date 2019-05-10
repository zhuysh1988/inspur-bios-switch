
// #include "json.hpp"

#include <com/inspur/BiosSwitch/Bios/server.hpp>
#include <iostream>
#include <memory>
#include <sdbusplus/sdbus.hpp>
#include <sdeventplus/event.hpp>
#include <vector>

namespace inspur
{
namespace biosswitch
{
namespace bios
{
// using json = nlohmann::json;
using BiosObject = sdbusplus::server::object_t<
    sdbusplus::com::inspur::BiosSwitch::server::Bios>;

class Bios : public BiosObject
{
  public:
    Bios(sdbusplus::bus::bus& bus, const std::string& path,
         sdeventplus::Event& event) :
        BiosObject(bus, path.c_str())
    {
      BiosObject::timeout(600);
      BiosObject::isChanged(false);
      BiosObject::autoSwitch(getSwitchMod());
      BiosObject::runningIndex(initBiosPresent());
    }

  bool autoSwitch(bool value) override;
  std::string runningIndex(std::string value) override;

  private:
    std::string initBiosPresent();
    bool getSwitchMod();
};
} // namespace bios
} // namespace biossswitch
} // namespace inspur
