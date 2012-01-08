#ifndef PROCESSOR_H
#define PROCESSOR_H

/*!
    \file processor.h
    \ingroup global
    \brief 协议类型
*/

enum EProcessorType{
	EPI_LOGIN,
	EPI_INFORMATION,
	EPI_COMMAND,
	EPI_UserRegister,
	EPI_ControlRole,
	EPI_HallTalk,

    EPI_UserType=0x0100,
    EPI_MaxType=0x1000,
};

#endif // PROCESSOR_H
