// ============================================================================
// ============================================================================
// Vrf:
// ---
// This class represents a VRF that is "active" in the DHCP relay server.
// 1) Content:
//    -------
// Each Vrf object, will have:
// 1.1) At least one "incoming" interface, i.e. - an interface from which DHCP
//      message (mostly Discovery) will arrive from.
// 1.2) At least one IPv4 address of the actual DHCP server of this VRF. For
//      example, it might simply be a DHCP server located at the "other" side
//      of the IP/MPLS backbone.
// 
// 2) Lifecycle:
//    ---------
// 2.1) Upon creation of the Vrf object, it is being intiazlied with its list
//      of interfaces. 
// 2.2) For each such interface, an IN socket needs to be created, binded so
//      that it would be ready to recive incoming DHCP Discovery (and other)
//      messages.
//
//
// ============================================================================
// ============================================================================
#pragma once

#include <vector>
#include <string>

#include "../../infra/include/utilities.h"

class Vrf
{
public:
     Vrf(const std::vector<std::string>& interfacesList);
    ~Vrf();

    // Non copyable
    Vrf(const Vrf& other) = delete;
    Vrf& operator=(const Vrf& rhs) = delete;

    // Public API:
    Result SetInterfaces();

private:
    std::vector<std::string> m_interfaceList;
};