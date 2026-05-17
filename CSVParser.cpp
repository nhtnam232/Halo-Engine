#include"CSVParser.h"


EventType stringToEventType(const std::string& eventStr) {
    if (eventStr == "LOGIN") return LOGIN;
    if (eventStr == "LOGOUT") return LOGOUT;
    if (eventStr == "TOKEN_REFRESH") return TOKEN_REFRESH;
    if (eventStr == "ACCESS") return ACCESS;
    if (eventStr == "FAILED_LOGIN") return FAILED_LOGIN;


    if (eventStr == "OPEN_APP" || eventStr == "OPEN APP") return OPEN_APP;

    if (eventStr == "DOWNLOAD") return DOWNLOAD;
    if (eventStr == "ADMIN_ACTION") return ADMIN_ACTION;

    return ACCESS;
}

int splitCSVLine(const std::string& line, std::string fields[7]) {
    for (int j = 0; j < 7; j++) {
        fields[j] = "";
    }

    std::stringstream ss(line);
    std::string token = "";
    int i = 0;

    while (std::getline(ss, token, ',') && i < 7) {

        while (!token.empty() && token[0] == ' ') {
            token.erase(0, 1);
        }

        while (!token.empty() && (token.back() == '\r' || token.back() == ' ')) {
            token.pop_back();
        }

        fields[i++] = token;
    }
    return i;
}
