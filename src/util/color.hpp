#ifndef UTIL_COLOR_HPP
#define UTIL_COLOR_HPP

#include <string>
#include <unordered_map>

struct color_t {
  // clang-format off
  enum e {
    // Regular text
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,

    // Regular bold text
    BoldBlack, BoldRed, BoldGreen, BoldYellow, BoldBlue, BoldMagenta, BoldCyan, BoldWhite,

    // Regular underline text
    UlBlack, UlRed, UlGreen, UlYellow, UlBlue, UlMagenta, UlCyan, UlWhite,

    // Regular background
    BlackBg, RedBg, GreenBg, YellowBg, BlueBg, MagentaBg, CyanBg, WhiteBg,

    // High intensty background
    BlackHiBg, RedHiBg, GreenHiBg, YellowHiBg, BlueHiBg, MagentaHiBg, CyanHiBg, WhiteHiBg,

    // High intensty text
    HiBlack, HiRed, HiGreen, HiYellow, HiBlue, HiMagenta, HiCyan, HiWhite,

    // Bold high intensity text
    BoldHiBlack, BoldHiRed, BoldHiGreen, BoldHiYellow, BoldHiBlue, BoldHiMagenta, BoldHiCyan, BoldHiWhite,

    // Reset
    End,

    // Not a color (plaintext)
    Nil = -1
  };
  // clang-format on
};

namespace color_str {

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

extern const std::vector<color_str::color_code> codes;

bool is_colored(color_t::e color);

}  // namespace color_str

#endif  // UTIL_COLOR_HPP
