#Initialization
AC_PREREQ([2.69])
AC_INIT([bios-switch], [1.0], [https://github.com/inspur-bmc/bios-switch/issues])
AC_LANG([C++])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

#Checks for programs.
AC_PROG_CXX
AM_PROG_AR
AC_PROG_INSTALL #Checks/sets the install variable to be used
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_CHECK_PROG([DIRNAME], dirname, dirname)

#Checks for libraries.
PKG_CHECK_MODULES([SYSTEMD], [libsystemd >= 221])

#Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_17([noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

#For libtools
LT_INIT

#Checks for header files.
PKG_CHECK_MODULES([INSPUR_DBUS_INTERFACES], [inspur-dbus-interfaces])
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus],, [AC_MSG_ERROR([Could not find sdbusplus...openbmc/sdbusplus package required])])
PKG_CHECK_MODULES([SDEVENTPLUS], [sdeventplus],, [AC_MSG_ERROR([The openbmc/sdeventplus package is required])])
#AC_CHECK_HEADER(nlohmann/json.hpp, [], [AC_MSG_ERROR([Could not find nlohmann/json.hpp])])

PKG_PROG_PKG_CONFIG
AC_ARG_WITH([systemdsystemunitdir],
     [AS_HELP_STRING([--with-systemdsystemunitdir=DIR], [Directory for systemd service files])],,
     [with_systemdsystemunitdir=auto])
AS_IF([test "x$with_systemdsystemunitdir" = "xyes" -o "x$with_systemdsystemunitdir" = "xauto"], [
     def_systemdsystemunitdir=$($PKG_CONFIG --variable=systemdsystemunitdir systemd)

     AS_IF([test "x$def_systemdsystemunitdir" = "x"],
   [AS_IF([test "x$with_systemdsystemunitdir" = "xyes"],
    [AC_MSG_ERROR([systemd support requested but pkg-config unable to query systemd package])])
    with_systemdsystemunitdir=no],
   [with_systemdsystemunitdir="$def_systemdsystemunitdir"])])
AS_IF([test "x$with_systemdsystemunitdir" != "xno"],
      [AC_SUBST([systemdsystemunitdir], [$with_systemdsystemunitdir])])
AM_CONDITIONAL([HAVE_SYSTEMD], [test "x$with_systemdsystemunitdir" != "xno"])

AC_DEFINE(INSPUR_BIOS_NAME, "com.inspur.BiosSwitch", [bios service.])
AC_DEFINE(INSPUR_BIOS_PATH, "/com/inspur/bios", [bios path.])

#Create configured output
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([inspur-bios-switch.service])
AC_OUTPUT
