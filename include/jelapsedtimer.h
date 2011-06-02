#ifndef JELAPSEDTIMER_H
#define JELAPSEDTIMER_H

#if QT_VERSION >= 0x040700
	#include <QElapsedTimer>
	typedef QElapsedTimer JElapsedTimer;
#else
	#include <QTime>
	typedef QTime JElapsedTimer;
#endif

#endif //JELAPSEDTIMER_H
