#include "widget.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <vector>

class WidgetImpl
{
public:
    std::string name;

    std::vector<std::string> history;

    mutable std::mutex mutex;

    std::ofstream logfile;

    WidgetImpl()
    {
        logfile.open("widget.log", std::ios::app);
    }

    ~WidgetImpl()
    {
        logfile.close();
    }

    void Log(const std::string& message)
    {
        auto now = std::chrono::system_clock::now();

        auto time = std::chrono::system_clock::to_time_t(now);

        logfile << std::put_time(std::localtime(&time),
                                 "%F %T")
                << " : "
                << message
                << '\n';
    }
};

Widget::Widget()
    : impl_(std::make_unique<WidgetImpl>())
{
}

Widget::~Widget() = default;

Widget::Widget(Widget&&) noexcept = default;

Widget&
Widget::operator=(Widget&&) noexcept = default;

void Widget::SetName(const std::string& name)
{
    std::lock_guard<std::mutex> lock(impl_->mutex);

    impl_->name = name;

    impl_->history.push_back(name);

    impl_->Log("Name changed to " + name);
}

std::string Widget::GetName() const
{
    std::lock_guard<std::mutex> lock(impl_->mutex);

    return impl_->name;
}

void Widget::PrintInfo() const
{
    std::lock_guard<std::mutex> lock(impl_->mutex);

    std::cout << "Current Name : "
              << impl_->name
              << '\n';

    std::cout << "History\n";

    for (const auto& item : impl_->history)
    {
        std::cout << "  - "
                  << item
                  << '\n';
    }
}
