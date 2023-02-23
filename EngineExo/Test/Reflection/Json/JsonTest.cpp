#include "JsonTest.h"
#include <filesystem>
#include <fstream>

void Test::JsonTest::Test()
{
    const std::string _path = std::filesystem::current_path().parent_path().string();
    // A a = A();
    // std::ofstream _outFile = std::ofstream(_path + "\\a.asset");
    // a.Serialize(_outFile);
    
    // A b = A();
    // std::ifstream _inFile = std::ifstream(_path + "\\a.asset");
    // b.DeSerialize(_inFile);
    // _inFile.close();
    //
    // LOG(b)

    
}
