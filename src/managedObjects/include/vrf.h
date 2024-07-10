// ============================================================================
// ============================================================================
// Vrf:
// ---
// This class represents a VRF that is "active" in the DHCP relay server.
// 1) Each Vrf object, will have:
// 1.1) At least one "incoming" interface, i.e. - an interface from which DHCP
//      message (mostly Discovery) will arrive from.
// 1.2) At least one IPv4 address of the actual DHCP server of this VRF. For
//      example, it might simply be a DHCP server located at the "other" side
//      of the IP/MPLS backbone.
// 2) Lifecycle:
//  
// ============================================================================
// ============================================================================
#pragma once

#include <vector>
#include <string>

class Vrf
{
public:
     Vrf(const std::string& interface);
    ~Vrf();

    // Non copyable
    Vrf(const Vrf& other) = delete;
    Vrf& operator=(const Vrf& rhs) = delete;

private:
    std::vector<std::string> m_interfaceList;
};