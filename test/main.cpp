
#include <iostream>
#include <fstream>


#include "ssp4cpp.hpp"

using namespace std;

int main()
{
    // using namespace ssp4cpp::ssp1::ssd;
    cout << "Starting parsing\n";

    auto ssd = ssp4cpp::ssp1::ssd::parse_system_structure("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/resources/SystemStructure_short.ssd");

    ofstream myfile;
    myfile.open ("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/resources/parsed.txt");
    myfile << ssd;
    myfile.close();


    // cout << endl << ssd << endl;

    cout << "Parsing complete\n";
}