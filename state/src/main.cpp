#include "diagnostic_connection.h"

int main() {

    DiagnosticConnection connection;

    connection.sendRequest(); // Rejected
    connection.connect();
    connection.sendRequest(); // Sent
    connection.disconnect();
    connection.sendRequest(); // Rejected
}