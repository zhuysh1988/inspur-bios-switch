#include "config.h"
#include "Bios.hpp"
// #include "Manager.hpp"
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/manager.hpp>
#include <sdeventplus/event.hpp>

int main() {
  auto event = sdeventplus::Event::get_default();
  auto bus = sdbusplus::bus::new_default();

  bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);

  // auto manager = std::make_shared<inspur::biosswitch::bios::Bios>(
  //     bus, INSPUR_BIOS_PATH, event);
  inspur::biosswitch::bios::Bios bios{bus, INSPUR_BIOS_PATH, event};
  // auto manager = std::make_shared<inspur::assets::manager::Manager>(
  //     bus, INSPUR_BIOS_PATH, event);

  bus.request_name(INSPUR_BIOS_NAME);

  return event.loop();
}
