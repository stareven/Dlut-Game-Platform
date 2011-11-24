#ifndef JCODEERROR_H
#define JCODEERROR_H

#include "jglobal.h"

const JCode ESuccess = 0;

const JCode EUnknownError = 0x00FF;

const JCode EDeveloping = 0x0100;

const JCode ENetworkError = 0x0200;
const JCode ECannotGetContentLengthInHead = ENetworkError | 0x0001;
const JCode EContentLengthIsZero = ENetworkError | 0x0002;

const JCode EPermissionError = 0x0300;
const JCode EPermissionDenied = EPermissionError | 0x0001;

const JCode EUserError = 0x0400;
const JCode ENoSuchUser = EUserError | 0x0001;

const JCode EFileSystemError = 0x0700;
const JCode EMakeDirFailed = EFileSystemError | 0x0001;
const JCode EOpenFileFailed = EFileSystemError | 0x0002;

#endif // JCODEERROR_H
