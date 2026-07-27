#include "widget.h"

#include <iostream>

int main()
{
    Widget widget;

    widget.SetName("Engine");

    widget.SetName("Transmission");

    widget.SetName("Braking");

    std::cout
        << "Current Widget : "
        << widget.GetName()
        << "\n\n";

    widget.PrintInfo();

    return 0;
}
