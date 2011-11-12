#ifndef JDIALOGUPDATEUSERINFO_H
#define JDIALOGUPDATEUSERINFO_H

#include <QDialog>

namespace Ui {
    class JDialogUpdateUserInfo;
}

class JUploadUserInfo;
class JUserInfo;

class JDialogUpdateUserInfo : public QDialog
{
    Q_OBJECT

public:
    explicit JDialogUpdateUserInfo(QWidget *parent = 0);
    ~JDialogUpdateUserInfo();
	void setInitUserInfo(const JUserInfo& userinfo);
	void accept();
private:
    Ui::JDialogUpdateUserInfo *ui;
	JUploadUserInfo* m_upload;
};

#endif // JDIALOGUPDATEUSERINFO_H
