#ifndef JWIDGETHALLTALK_H
#define JWIDGETHALLTALK_H

#include <QWidget>

namespace Ui {
    class JWidgetHallTalk;
}
class JClientHallTalkProcessor;
class JRequestUserInfo;

class JWidgetHallTalk : public QWidget
{
    Q_OBJECT

public:
    explicit JWidgetHallTalk(QWidget *parent = 0);
    ~JWidgetHallTalk();

private:
    Ui::JWidgetHallTalk *ui;
	JClientHallTalkProcessor* m_processor;
	JRequestUserInfo* m_requserinfo;
private slots:
	void showMessage(const QString& msg);
	void sendMessageInEdit();
};

#endif // JWIDGETHALLTALK_H
