# assets module

just a build framework


# How To

```
1. devtool add inspur-bios-switch https://github.com/inspur-bmc/inspur-bios-switch.git
2. modify inspur-bios-switch_git.bb ,add
        DEPENDS += "autoconf-archive-native"
        DEPENDS += "inspur-dbus-interfaces"
        DEPENDS += "sdbusplus"
        DEPENDS += "sdeventplus"
        DEPENDS += "systemd"
        DEPENDS += "nlohmann-json"

        SYSTEMD_SERVICE_${PN} += "inspur-bios-switch.service"

        inherit pythonnative
        inherit systemd


3. bitbake inspur-bios-switch
```
