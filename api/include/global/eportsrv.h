#ifndef EPORTSRV_H
#define EPORTSRV_H

/*!
	\file eportsrv.h
	\ingroup global
	\brief MainServer提供的服务与端口相关的定义。
*/

enum EPSProtocol{EPP_LOGINHASH,EPP_PORT};

/*!
	\brief MainServer提供的各项服务。
*/
enum EServerType{	
	EST_LOGIN, /**< 用户登录 */
	EST_GAMEINFO, /**< 游戏列表及游戏相信 */
	EST_FREEPORT, /**< 查询Login和SecretPort服务的端口 */
	EST_SECRETPORT, /**< 查询除FreePort及FreePort包含以外服务的端口 */
	EST_SUBSERVER, /**< 上传子服务器信息 */
	EST_USERINFO, /**< 查询用户信息 */
	EST_MAX, /**< 服务的数目 */
};

#define isInFree(type) ( EST_LOGIN==type || EST_SECRETPORT== type)

#endif // EPORTSRV_H
