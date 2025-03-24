#include <iostream>

#include "./core/System.hpp"

int main(int argc, char** argv)
{
    TCMS::System::Init(argc, argv);
    TCMS::System::Run();
    TCMS::System::ShutDown();
}
