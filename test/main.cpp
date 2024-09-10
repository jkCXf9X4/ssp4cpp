
#include <iostream>
#include <fstream>


#include "ssp_import.hpp"

using namespace std;

int main()
{
    // Opening zip
    cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/resources/embrace.ssp");

    cout << ssp << endl;

    ofstream myfile;
    myfile.open ("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/resources/parsed.txt");
    myfile << ssp.ssd;
    myfile.close();


    cout << "Parsing complete\n";
}