
#include <iostream>
#include "ssp4cpp.hpp"

using namespace std;

int main()
{
    cout << "Starting parsing\n";

    auto ssd = ssp4cpp::ssp1::parse_system_structure("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/resources/SystemStructure.ssd");

    // cout << ssd;

    cout << "Parsing complete\n";
}