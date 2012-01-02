#ifndef COMMAND_H
#define COMMAND_H

/*!
	\file command.h
	\ingroup global
	\brief COMMAND协议需要用到的参数
*/

/*!
	\brief 命令类型
*/
enum ECommandType{
	ECT_Shutdown, ///< 关闭
	ECT_Restart, ///< 重新启动
};

#endif // COMMAND_H
