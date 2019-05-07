AM_DEFAULT_SOURCE_EXT = .cpp

sbin_PROGRAMS = inspur-bios-switch

if HAVE_SYSTEMD
systemdsystemunit_DATA = inspur-bios-switch.service
endif

inspur_bios_switch_SOURCES = \
	main.cpp  \
	Bios.cpp 

BUILT_SOURCES =

inspur_bios_switch_LDADD = \
              ${INSPUR_DBUS_INTERFACES_LIBS} \
		      $(SDBUSPLUS_LIBS) \
		      $(SDEVENTPLUS_LIBS)

inspur_bios_switch_CXXFLAGS =  \
              ${INSPUR_DBUS_INTERFACES_CFLAGS} \
		      $(SDBUSPLUS_CFLAGS) \
		      $(SDEVENTPLUS_CFLAGS)

