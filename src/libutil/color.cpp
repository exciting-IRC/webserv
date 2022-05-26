#include <libutil/color.hpp>

namespace color {

inline static const string _color(const string& code) {
  static const string begin = "\001\033[", end = "\002m";

  return begin + code + end;
}

// Regular text

const string BLK = _color("0;30");
const string RED = _color("0;31");
const string GRN = _color("0;32");
const string YEL = _color("0;33");
const string BLU = _color("0;34");
const string MAG = _color("0;35");
const string CYN = _color("0;36");
const string WHT = _color("0;37");

// Regular bold text
const string BBLK = _color("1;30");
const string BRED = _color("1;31");
const string BGRN = _color("1;32");
const string BYEL = _color("1;33");
const string BBLU = _color("1;34");
const string BMAG = _color("1;35");
const string BCYN = _color("1;36");
const string BWHT = _color("1;37");

// Regular underline text
const string UBLK = _color("4;30");
const string URED = _color("4;31");
const string UGRN = _color("4;32");
const string UYEL = _color("4;33");
const string UBLU = _color("4;34");
const string UMAG = _color("4;35");
const string UCYN = _color("4;36");
const string UWHT = _color("4;37");

// Regular background
const string BLKB = _color("40");
const string REDB = _color("41");
const string GRNB = _color("42");
const string YELB = _color("43");
const string BLUB = _color("44");
const string MAGB = _color("45");
const string CYNB = _color("46");
const string WHTB = _color("47");

// High intensty background
const string BLKHB = _color("0;100");
const string REDHB = _color("0;101");
const string GRNHB = _color("0;102");
const string YELHB = _color("0;103");
const string BLUHB = _color("0;104");
const string MAGHB = _color("0;105");
const string CYNHB = _color("0;106");
const string WHTHB = _color("0;107");

// High intensty text
const string HBLK = _color("0;90");
const string HRED = _color("0;91");
const string HGRN = _color("0;92");
const string HYEL = _color("0;93");
const string HBLU = _color("0;94");
const string HMAG = _color("0;95");
const string HCYN = _color("0;96");
const string HWHT = _color("0;97");

// Bold high intensity text
const string BHBLK = _color("1;90");
const string BHRED = _color("1;91");
const string BHGRN = _color("1;92");
const string BHYEL = _color("1;93");
const string BHBLU = _color("1;94");
const string BHMAG = _color("1;95");
const string BHCYN = _color("1;96");
const string BHWHT = _color("1;97");

// Reset
const string END = _color("0");

}  // namespace color
