# State Design Pattern in C++

## Overview

The **State design pattern** allows an object to change its behavior when its internal state changes. It is a behavior design pattern.

This example models a diagnostic connection with two states:

- **Disconnected:** Rejects diagnostic requests.
- **Connected:** Sends diagnostic requests.

The connection delegates request handling to its current state object.

## Pattern Participants

| Participant | Class | Responsibility |
|---|---|---|
| State interface | `ConnectionState` | Declares `sendRequest()` |
| Concrete state | `DisconnectedState` | Rejects requests when disconnected |
| Concrete state | `ConnectedState` | Sends requests when connected |
| Context | `DiagnosticConnection` | Maintains the current state and delegates requests |

## How It Works

1. The connection starts in `DisconnectedState`.
2. Calling `sendRequest()` rejects the request.
3. Calling `connect()` changes the current state to `ConnectedState`.
4. Calling `sendRequest()` now sends the request.
5. Calling `disconnect()` changes the state back to `DisconnectedState`.

```cpp
DiagnosticConnection connection;

connection.sendRequest(); // Rejected
connection.connect();
connection.sendRequest(); // Sent
connection.disconnect();
connection.sendRequest(); // Rejected
```

## Project Structure

Place these files in the same directory:

- `main.cpp` — State pattern implementation and demonstration.
- `CMakeLists.txt` — CMake build configuration.
- `README.md` — Documentation.

## Requirements

- C++17-compatible compiler
- CMake 3.16 or later

## Build and Run

Run these commands from the project directory:

```bash
cmake -S . -B build
cmake --build build
./build/state_pattern
```

For Windows with a Visual Studio generator:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\state_pattern.exe
```

## Expected Output

```text
Rejected: connection unavailable
Sending diagnostic request
Rejected: connection unavailable
```

## Ownership and Lifetime

The concrete state objects are members of `DiagnosticConnection`:

```cpp
DisconnectedState disconnected_;
ConnectedState connected_;
const ConnectionState* state_ = &disconnected_;
```

- The connection owns both state objects.
- `state_` is a non-owning pointer to the active state.
- Both states remain alive throughout the connection object's lifetime.
- Changing state only updates the pointer.
- State transitions do not require heap allocation.

### Why Are Copy and Move Operations Deleted?

Default copying or moving would copy the address stored in `state_`.

The destination object's pointer could then refer to a state member of the
source object. If the source were destroyed, that pointer would dangle.

Copy and move operations are therefore deleted. Supporting them would
require explicitly rebinding the pointer to the destination's corresponding
state member.

## Advantages

- Encapsulates state-specific behavior in separate classes.
- Reduces repeated state checks across operations.
- Separates the context from concrete state behavior.
- Makes individual state behavior easier to test.

## Drawbacks

- Introduces additional classes and virtual dispatch.
- Can be excessive for a simple state machine.
- Transition logic can become scattered if responsibilities are unclear.
- Adding a state may require changes to the context and transition logic.

For a small state machine, an `enum` and `switch` may be simpler.

## State vs. Strategy

| State | Strategy |
|---|---|
| Represents an object's lifecycle condition | Represents an interchangeable algorithm |
| Behavior changes as state transitions occur | Behavior changes when a different strategy is selected |
| Example: connected or disconnected | Example: fixed-delay or exponential retry |
| Transitions follow lifecycle rules | Selection usually comes from the client or configuration |

## Limitations of This Example

- The implementation is single-threaded.
- `connect()` assumes connection establishment succeeds.
- No actual network communication occurs.
- Connection timeouts and error recovery are not implemented.
- Concurrent state reads and writes require synchronization.

A production implementation must coordinate state transitions with request
execution. Making the state pointer atomic alone does not solve the entire
connection-lifecycle problem.

## Questions and Answers

### 1. What problem does the State pattern solve?

It encapsulates behavior that depends on an object's current state.
The context delegates operations to its active state object instead of
repeating state-dependent conditions throughout its implementation.

### 2. Who controls state transitions?

In this example, `DiagnosticConnection` controls transitions through
`connect()` and `disconnect()`.

Other designs allow concrete state objects to request transitions.

### 3. Why use a pointer for the current state?

A pointer can be redirected to another existing state object.

Both concrete states remain alive as members of the connection, so switching
state does not require constructing or destroying objects.

### 4. Why does the state interface have a virtual destructor?

A virtual destructor supports correct destruction of a derived state through
a base-class pointer.

This example does not delete states through `state_`, but the interface
supports safe polymorphic destruction.

### 5. Is this implementation thread-safe?

No. Concurrent calls that read and modify `state_` can cause a data race.

A production design could serialize events through one worker thread or
protect shared state with synchronization.

### 6. When would you choose an enum and switch instead?

When there are few states, simple transitions, and little state-specific
behavior.

The State pattern becomes more useful when multiple operations behave
differently in each state.

### 7. How would you add a Connecting state?

Create a `ConnectingState` implementation, add its storage to the context,
and define transitions for connection success, failure, and timeout.

Also define how requests are handled while connecting.

### 8. What if the connection drops after a request is queued?

Revalidate the connection when executing the request and handle transport
failure even after validation.

Define whether queued requests should fail, be cancelled, or wait for
reconnection with a deadline. Retry only when the operation permits it.

## Summary

> State encapsulates state-specific behavior in separate classes.
> The context delegates operations to its current state, and transitions
> change its behavior. It is useful when lifecycle-dependent logic becomes
> complex or repeated across multiple operations.