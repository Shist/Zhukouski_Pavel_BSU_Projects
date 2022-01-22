#pragma once

enum class MessageType : char
{
    STC_SESSION_KEY,
    STC_FILE,
    STC_UNABLE_TO_SEND_FILE,
    STC_AUTH_SUCCESSFUL,
    STC_AUTH_FAILED,

    CTS_RSA_KEY,
    CTS_FILE_REQUEST,
    CTS_AUTH_REQUEST
};
