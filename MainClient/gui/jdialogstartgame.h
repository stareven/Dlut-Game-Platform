#ifndef JDIALOGSTARTGAME_H
#define JDIALOGSTARTGAME_H

#include <Global/Global>

#include <QDialog>

namespace Ui {
    class JDialogStartGame;
}
class JGameClientLoader;

class JDialogStartGame : public QDialog
{
    Q_OBJECT

public:
    explicit JDialogStartGame(QWidget *parent = 0);
	~JDialogStartGame();
	void setGameId(JID gameId);
	int exec();
private:
    Ui::JDialogStartGame *ui;
	JGameClientLoader* m_gameClientLoader;
	JID m_gameId;
private slots:
	void download_begin();
	void download_rcvTotalSize(qint64 size);
	void download_progress(qint64,qint64);
	void download_finished();
	void download_error();
};

#endif // JDIALOGSTARTGAME_H
