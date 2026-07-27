# Pimpl Idiom (Pointer to Implementation)

## Overview

The **Pimpl Idiom** (Pointer to Implementation) is a C++ technique used to hide implementation details from the public interface.

It reduces compile-time dependencies, improves encapsulation, and helps maintain binary compatibility (ABI stability).

---

## Project Structure

```text
pimpl-idiom/
├── include/
│   └── widget.h
├── src/
│   ├── widget.cpp
│   └── main.cpp
├── README.md
└── CMakeLists.txt
```

---

## Without Pimpl

```cpp
class Widget
{
private:
    std::mutex mutex_;
    std::ofstream file_;
    std::vector<std::string> history_;
};
```

Changing any private member requires recompiling every translation unit that includes the header.

---

## With Pimpl

```cpp
class WidgetImpl;

class Widget
{
private:
    std::unique_ptr<WidgetImpl> impl_;
};
```

The implementation is hidden inside `widget.cpp`.

---

## Advantages

- Hides implementation details
- Reduces compilation time
- Cleaner public headers
- Better ABI stability
- Fewer header dependencies
- Easier maintenance of large libraries

---

## Disadvantages

- One heap allocation
- One pointer indirection
- Slightly more boilerplate

---

## Why is the destructor defined in the `.cpp` file?

`std::unique_ptr<WidgetImpl>` destroys the implementation object.

At the point of destruction, `WidgetImpl` must be a complete type.

Since `WidgetImpl` is only forward-declared in the header, the destructor is defined in `widget.cpp`, where the full definition is available.

---

## Where is Pimpl used?

- Qt (D-pointer pattern)
- LLVM
- Chromium
- Large SDKs
- Database engines
- Adaptive AUTOSAR middleware
- Automotive libraries

---

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Run:

```bash
./pimpl_demo
```

---

## Design

```text
              +----------------+
              |    Widget      |
              +----------------+
              | unique_ptr     |
              +--------+-------+
                       |
                       v
             +-------------------+
             |   WidgetImpl      |
             +-------------------+
             | std::string       |
             | std::mutex        |
             | std::ofstream     |
             | std::vector       |
             +-------------------+
```

---

## Key Takeaways

- Keep headers small and stable.
- Hide implementation details in `.cpp` files.
- Reduce recompilation when implementation changes.
- Improve ABI compatibility for shared libraries.
- Use `std::unique_ptr` for automatic lifetime management.

