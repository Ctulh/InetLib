//
// Created by ctuh on 8/4/23.
//

#pragma once

#include <sys/errno.h>

namespace Error {
    static int getLastError() {
        int error = errno;
        return error;
    }
}
