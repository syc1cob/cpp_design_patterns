#pragma once

#include "disconnected_state.h"
#include "connected_state.h"

/*DiagnosticConnection is the context. It holds the current state and delegates sendRequest() to it. 
The context manages transitions in this example; concrete states can also request transitions in other designs.
The state objects are members, so switching state does not require heap allocation.
*/
class DiagnosticConnection {
public:
    void connect();
    void disconnect() ;
    void sendRequest() const;

    // state_ points to a member of this object.
    // Prevent copying/moving from leaving it pointing into another object.
    DiagnosticConnection() = default;
    DiagnosticConnection(const DiagnosticConnection&) = delete;
    DiagnosticConnection& operator=(const DiagnosticConnection&) = delete;
    DiagnosticConnection(DiagnosticConnection&&) = delete;
    DiagnosticConnection& operator=(DiagnosticConnection&&) = delete;

private:
    DisconnectedState disconnected_;
    ConnectedState connected_;
    const ConnectionState* state_ = &disconnected_;
};