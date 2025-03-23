#include <iostream>

#include "./core/System.hpp"

int main()
{
    TCMS::System::Init();
    TCMS::System::Run();
    TCMS::System::ShutDown();
}