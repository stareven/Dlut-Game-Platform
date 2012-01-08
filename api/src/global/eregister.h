#ifndef EREGISTER_H
#define EREGISTER_H

/*!
    \file eregister.h
    \ingroup global
    \brief 与用户注册相关的类型定义
*/

/*!
    \brief 注册结果
*/
enum ERegister{
	ER_SUCCESS, ///< 注册结果
	ER_PermissionDenied, ///< 权限不够
	ER_RoleOverflow, ///< 身份值溢出
	ER_LoginNameExists, ///< 已存在相同的用户名
	ER_LoginNameLengthError, ///< 用户名长度非法
	ER_PasswordLengthError, ///< 密码长度非法
	ER_UserIdFull, ///< 用户ID已满，不能再继续注册用户
};

#endif // EREGISTER_H
