//
// Created by ctuh on 8/3/23.
//

#pragma once

#include <sys/socket.h>
#include <sys/types.h>

template<int level, int option, typename StructType>
class SocketFlagsManipulator {
public:
    static bool setFlag(int socketFd, StructType const& optionValue) {
        socklen_t structSize = sizeof(StructType);
        int result = setsockopt(socketFd, level, option, &optionValue, structSize);
        return result != -1;
    }
};
