#ifndef LIBUTIL_COLOR_HPP
#define LIBUTIL_COLOR_HPP

#include <string>
#include <unordered_map>

namespace color {

using std::string;
// Regular text

extern const string BLK;
extern const string RED;
extern const string GRN;
extern const string YEL;
extern const string BLU;
extern const string MAG;
extern const string CYN;
extern const string WHT;

// Regular bold text
extern const string BBLK;
extern const string BRED;
extern const string BGRN;
extern const string BYEL;
extern const string BBLU;
extern const string BMAG;
extern const string BCYN;
extern const string BWHT;

// Regular underline text
extern const string UBLK;
extern const string URED;
extern const string UGRN;
extern const string UYEL;
extern const string UBLU;
extern const string UMAG;
extern const string UCYN;
extern const string UWHT;

// Regular background
extern const string BLKB;
extern const string REDB;
extern const string GRNB;
extern const string YELB;
extern const string BLUB;
extern const string MAGB;
extern const string CYNB;
extern const string WHTB;

// High intensty background
extern const string BLKHB;
extern const string REDHB;
extern const string GRNHB;
extern const string YELHB;
extern const string BLUHB;
extern const string MAGHB;
extern const string CYNHB;
extern const string WHTHB;

// High intensty text
extern const string HBLK;
extern const string HRED;
extern const string HGRN;
extern const string HYEL;
extern const string HBLU;
extern const string HMAG;
extern const string HCYN;
extern const string HWHT;

// Bold high intensity text
extern const string BHBLK;
extern const string BHRED;
extern const string BHGRN;
extern const string BHYEL;
extern const string BHBLU;
extern const string BHMAG;
extern const string BHCYN;
extern const string BHWHT;

// Reset
extern const string END;

}  // namespace color

// Reference
// https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a

#endif  // LIBUTIL_COLOR_HPP
