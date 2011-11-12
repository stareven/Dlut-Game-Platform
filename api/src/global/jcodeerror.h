#ifndef JCODEERROR_H
#define JCODEERROR_H

#include "jglobal.h"

const JCode ESuccess = 0;

const JCode ENetworkError = 0x0200;


const JCode EPermissionError = 0x0300;
const JCode EPermissionDenied = EPermissionError | 0x0001;

const JCode EUserError = 0x0400;
const JCode ENoSuchUser = EUserError | 0x0001;

#endif // JCODEERROR_H
