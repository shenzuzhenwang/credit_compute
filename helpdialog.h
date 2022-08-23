/********************************************************************************
** 帮助界面类
** 用于显示帮助界面
********************************************************************************/
#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QTextBrowser>
#include <QLayout>

class HelpDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

signals:

public slots:

private:
    QTextBrowser* text;
    QGridLayout* layout;
};

#endif // HELPDIALOG_H
