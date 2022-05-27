#include <util/color.hpp>
#include <util/comptime.hpp>
#include <vector>

namespace color_str {

using std::vector;

color_code _color_codes[] = {
    // Regular text
    BLK, RED, GRN, YEL, BLU, MAG, CYN, WHT,

    // Regular bold text
    BBLK, BRED, BGRN, BYEL, BBLU, BMAG, BCYN, BWHT,

    // Regular underline text
    UBLK, URED, UGRN, UYEL, UBLU, UMAG, UCYN, UWHT,

    // Regular background
    BLKB, REDB, GRNB, YELB, BLUB, MAGB, CYNB, WHTB,

    // High intensty background
    BLKHB, REDHB, GRNHB, YELHB, BLUHB, MAGHB, CYNHB, WHTHB,

    // High intensty text
    HBLK, HRED, HGRN, HYEL, HBLU, HMAG, HCYN, HWHT,

    // Bold high intensity text
    BHBLK, BHRED, BHGRN, BHYEL, BHBLU, BHMAG, BHCYN, BHWHT,

    // Reset
    END};

const vector<color_code> codes COMPTIME_CONTAINER_INIT(_color_codes);

}  // namespace color
