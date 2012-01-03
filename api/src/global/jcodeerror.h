#ifndef JCODEERROR_H
#define JCODEERROR_H

#include "jglobal.h"

/*!
    \file jcodeerror.h
    \ingroup global
    \brief 定义一些常用的 JCode 的值
*/

const JCode ESuccess = 0; ///< 成功

const JCode EUnknownError = 0x00FF; ///< 未知错误

const JCode EDeveloping = 0x0100; ///< 未完成的功能，尚在开发中

const JCode ENetworkError = 0x0200; ///< 网络错误
const JCode ECannotGetContentLengthInHead = ENetworkError | 0x0001; ///< 无法在http头信息中获得 ContentLength
const JCode EContentLengthIsZero = ENetworkError | 0x0002; ///< ContentLength 为零

const JCode EPermissionError = 0x0300; ///< 与权限相关的错误
const JCode EPermissionDenied = EPermissionError | 0x0001; ///< 权限不够

const JCode EUserError = 0x0400; ///< 与用户相关的错误
const JCode ENoSuchUser = EUserError | 0x0001; ///< 没有这个用户

const JCode EFileSystemError = 0x0700; ///< 文件系统错误
const JCode EMakeDirFailed = EFileSystemError | 0x0001; ///< 建立目录失败
const JCode EOpenFileFailed = EFileSystemError | 0x0002; ///< 打开文件失败

const JCode EUserCode = 0x1000; ///< 用户自定义值不得小于这个值
const JCode EMaxCode = 0xF000; ///< 用户自定义值不得大于这个值

#endif // JCODEERROR_H
