#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace graphite
{
    static void logMessage(const std::string &message)
    {
#ifdef GRAPHITE_DEBUG
        std::cout << message << std::endl;
#endif
    }
}

#endif //LOGGER_H
