#ifndef ELOGIN_H
#define ELOGIN_H

/*!
	\file elogin.h
	\ingroup global
	\brief 与登录相关的类型定义。
*/

/*!
	\brief 一个用户拥有的身份的组合
	每名用户能够拥有多个身份。我们按位记录一个用户拥有的身份的组合。
*/
typedef qint16 JRoleCombination;

/*!
	\brief 登录身份
*/
enum ERole{
	ROLE_GAMEPLAYER,/**< 游戏玩家*/
	ROLE_GAMEDESIGNER,/**< 游戏开发者*/
	ROLE_GAMESERVERRUNNER,/**< 游戏服务器运营维护员*/
	ROLE_ADMIN,/**< 平台管理员*/
	ROLE_ROOT/**< 根用户，并用于判断此枚举值的上限*/
};

/*!
	\brief 登录结果
*/
enum ELogin{
	EL_SUCCESS, /**< 登录成功 */
	EL_NO_SUCH_USER, /**< 没有此用户 */
	EL_PASSWD_WRONG, /**< 密码错误 */
	EL_NO_SUCH_ROLE, /**< 用户不具有此身份 */
	EL_ALREADY_LOGIN, /**< 已经登录，不能重复登录 */
	EL_NETWORK_ERROR, /**< 网络错误 */
};

/*!
    \brief 更改用户身份的动作
    详情请见 JRequestControlRole
*/
enum EControlRoleAction{
	ECRA_Add, ///< 添加一个身份
	ECRA_Remove, ///< 移除一个身份
};

#endif
