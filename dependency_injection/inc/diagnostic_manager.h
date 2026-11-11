#pragma once

#include "ilogger.h"

class DiagnosticManager {
public:
    explicit DiagnosticManager(ILogger& logger);

    void reportError();

private:
    ILogger& logger_;
};