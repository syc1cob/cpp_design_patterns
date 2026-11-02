#include "diagnostic_connection.h"

void DiagnosticConnection::connect() {
        // Assume connection establishment succeeded.
        state_ = &connected_;
}

void DiagnosticConnection::disconnect() {
        state_ = &disconnected_;
}

void DiagnosticConnection::sendRequest() const {
        state_->sendRequest();
}