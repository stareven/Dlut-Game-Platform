#ifndef JELAPSEDTIMER_H
#define JELAPSEDTIMER_H

/*!
	\file jelapsedtimer.h
	\ingroup global
	\brief 为了兼容Qt 4.7.0以前的版本，提供一个通用的计时器类。
*/

#if QT_VERSION >= 0x040700
	#include <QElapsedTimer>
	typedef QElapsedTimer JElapsedTimer;
#else
	#include <QTime>
	typedef QTime JElapsedTimer;
#endif

#endif //JELAPSEDTIMER_H
