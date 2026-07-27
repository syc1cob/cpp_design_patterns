#pragma once

#include <memory>
#include <string>

class WidgetImpl;

class Widget
{
public:
    Widget();
    ~Widget();

    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;

    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;

    void SetName(const std::string& name);

    std::string GetName() const;

    void PrintInfo() const;

private:
    std::unique_ptr<WidgetImpl> impl_;
};
