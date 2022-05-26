#include <libutil/color.hpp>
#include <libutil/util.hpp>
#include <vector>

namespace color {

struct colorHash {
  size_t operator()(const color_t::impl n) const { return static_cast<size_t>(n); }
};

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

const std::vector<color::color_code> codes(color::_color_codes,
                                           COMPTIME_ARRAY_END(color::_color_codes));
}  // namespace color
