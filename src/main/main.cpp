#include <fstream>
#include <iostream>
#include <libstrutil/strutil.hpp>
#include <libutil/types.hpp>
#include <main/main.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;


void erase_comments(string& line,const string& comment = "#" ) {
  string::size_type comment_index;

  if ((comment_index = line.find(comment)) != string::npos)
    line.erase(comment_index);
}

int main() {
  std::ifstream infile("/Users/youkim/Repo/webserv/config.conf");
  string line;
  for (i32 i = 0; std::getline(infile, line); i++) {
    erase_comments(line);

    vector<string> tokens = strutil::split(line);
    std::cout << "line " << i << std::endl;
    strutil::print_vector(tokens);
  }

  return 0;
}
