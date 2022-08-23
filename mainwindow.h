#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "pointtransform.h"
#include "helpdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void insert_row();
    void change_score();
    void clicked_allcheck();
    void change_allcheck();
    void Connections();
    float point_compute(int mark);

private slots:
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_cellChanged(int row, int column);

    void close();
    void open_file();
    void save_as();
    void closeEvent (QCloseEvent * );

private:
    Ui::MainWindow *ui;

    PointTransform* point_transform;

    HelpDialog* help_dialog;
};
#endif // MAINWINDOW_H
