
#include <stdio.h>
#include <stdexcept>
#include <iomanip>
#include <sstream>

using namespace std;

std::string format(){

    std::ostringstream s;

    s << std::setbase(16) << std::setw(2) << std::setfill('0') << 1 << " "
                 << std::setbase(16) << std::setw(2) << std::setfill('0') << 3
                 << std::endl;

    return s.str();
}
int main()
{
    std::string s = format();

    return 0;
}

