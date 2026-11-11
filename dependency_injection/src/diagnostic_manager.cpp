#include "diagnostic_manager.h"

DiagnosticManager::DiagnosticManager(ILogger& logger)
    : logger_(logger)
{
}

void DiagnosticManager::reportError()
{
    logger_.log("ECU communication failure");
}