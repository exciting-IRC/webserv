#ifndef LIBUTIL_COLOR_HPP
#define LIBUTIL_COLOR_HPP

#include <string>
#include <unordered_map>

struct color_t {
  // clang-format off
  enum impl {
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
    END
  };
  // clang-format on
};

namespace color {

using std::string;
typedef const std::string color_code;

// Regular text
extern color_code BLK, RED, GRN, YEL, BLU, MAG, CYN, WHT;

// Regular bold text
extern color_code BBLK, BRED, BGRN, BYEL, BBLU, BMAG, BCYN, BWHT;

// Regular underline text
extern color_code UBLK, URED, UGRN, UYEL, UBLU, UMAG, UCYN, UWHT;

// Regular background
extern color_code BLKB, REDB, GRNB, YELB, BLUB, MAGB, CYNB, WHTB;

// High intensty background
extern color_code BLKHB, REDHB, GRNHB, YELHB, BLUHB, MAGHB, CYNHB, WHTHB;

// High intensty text
extern color_code HBLK, HRED, HGRN, HYEL, HBLU, HMAG, HCYN, HWHT;

// Bold high intensity text
extern color_code BHBLK, BHRED, BHGRN, BHYEL, BHBLU, BHMAG, BHCYN, BHWHT;

// Reset
extern color_code END;

extern const std::vector<color::color_code> codes;
}  // namespace color

#endif  // LIBUTIL_COLOR_HPP
