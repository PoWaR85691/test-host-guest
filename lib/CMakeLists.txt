add_library(host-guest-lib SHARED
    baseconnection.h
    guestconnection.h guestconnection.cpp
    hostconnection.h hostconnection.cpp
    common.h common.cpp
)