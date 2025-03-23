#include <iostream>

#include "./models/System.hpp"

int main()
{
    using namespace TCMS;

    System::Init();
    System::Run();
    System::ShutDown();
}