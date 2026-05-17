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

std::string eventTypeToString(int type) {
    switch (type) {
    case 0: return "LOGIN";
    case 1: return "LOGOUT";
    case 2: return "TOKEN_REFRESH";
    case 3: return "ACCESS";
    case 4: return "FAILED_LOGIN";
    case 5: return "OPEN_APP";
    case 6: return "DOWNLOAD";
    case 7: return "ADMIN_ACTION";
    default: return "UNKNOWN";
    }
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
