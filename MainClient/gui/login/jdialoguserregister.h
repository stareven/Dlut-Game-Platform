#ifndef JDIALOGUSERREGISTER_H
#define JDIALOGUSERREGISTER_H

#include <QDialog>

namespace Ui {
	class JDialogUserRegister;
}
class JRequestUserRegister;

class JDialogUserRegister : public QDialog
{
    Q_OBJECT

public:
    explicit JDialogUserRegister(QWidget *parent = 0);
    ~JDialogUserRegister();
	void accept();
private:
    Ui::JDialogUserRegister *ui;
	JRequestUserRegister* m_register;
};

#endif // JDIALOGUSERREGISTER_H
