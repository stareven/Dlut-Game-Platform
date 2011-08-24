#ifndef ELOGIN_H
#define ELOGIN_H

/*!
	\file elogin.h
	\ingroup global
	\brief 与登录相关的类型定义。
*/

/*!
	\brief 每名用户能够以多个身份登录。我们按bit记录一个用户拥有的身份的组合。
*/
typedef qint16 JRole;

/*!
	\brief 登录身份
*/
enum ERole{
	ROLE_GAMEPLAYER,/**< 游戏玩家*/
	ROLE_GAMEDESIGNER,/**< 游戏开发者*/
	ROLE_GAMESERVERRUNNER,/**< 游戏服务器运营维护员*/
	ROLE_ADMIN,/**< 平台管理员*/
	ROLE_ROOT/**< 根用户*/
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
	EL_SOCKET_DISCONNECTED, /**< 连接断开 */
};

#endif
