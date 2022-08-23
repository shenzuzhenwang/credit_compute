#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    point_transform = new PointTransform(this);
    help_dialog = new HelpDialog(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(200);


    Connections();

    QFile file("temp_message");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);
        for (int i = 1; !stream.atEnd(); i++)
        {
            QStringList sl = stream.readLine().split(' ');
            ui->tableWidget->item(i, 0)->setText(sl[0]);
            ui->tableWidget->item(i, 1)->setText(sl[1]);
            ui->tableWidget->item(i, 2)->setText(sl[2]);
            ui->tableWidget->item(i, 3)->setCheckState(sl[3] == '0' ? Qt::Unchecked : Qt::Checked);
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insert_row()
{
    int row_count = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row_count);
    QFont font;
    font.setPointSize(12);
    QTableWidgetItem *tablewidgetitem = new QTableWidgetItem();
    tablewidgetitem->setTextAlignment(Qt::AlignCenter);
    tablewidgetitem->setFont(font);
    ui->tableWidget->setItem(row_count, 0, tablewidgetitem);
    QTableWidgetItem *tablewidgetitem1 = new QTableWidgetItem();
    tablewidgetitem1->setTextAlignment(Qt::AlignCenter);
    tablewidgetitem1->setFont(font);
    ui->tableWidget->setItem(row_count, 1, tablewidgetitem1);
    QTableWidgetItem *tablewidgetitem2 = new QTableWidgetItem();
    tablewidgetitem2->setTextAlignment(Qt::AlignCenter);
    tablewidgetitem2->setFont(font);
    ui->tableWidget->setItem(row_count, 2, tablewidgetitem2);
    QTableWidgetItem *tablewidgetitem3 = new QTableWidgetItem();
    tablewidgetitem3->setCheckState(Qt::Checked);
    tablewidgetitem3->setTextAlignment(Qt::AlignCenter);
    tablewidgetitem3->setFont(font);
    tablewidgetitem3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row_count, 3, tablewidgetitem3);
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if (item->row() == ui->tableWidget->rowCount() - 1 && (item->column() == 3 || item->text() != NULL))
    {
        ui->tableWidget->blockSignals(true);

        insert_row();

        ui->tableWidget->blockSignals(false);
    }
}

float MainWindow::point_compute(int mark)
{
    for (int i = 0; i < point_transform->point_range.size(); i++)
    {
        if (mark <= point_transform->point_range[i].range.first && mark >= point_transform->point_range[i].range.second)
        {
            return point_transform->point_range[i].point;
        }
    }
    return 0;
}

void MainWindow::change_score()
{
    float sum_credit = 0, sum_mark = 0, sum_point = 0;
    for (int i = 1; i < ui->tableWidget->rowCount() - 1; i++)
    {
        QString credit = ui->tableWidget->item(i, 1)->text();
        QString mark = ui->tableWidget->item(i, 2)->text();
        if (credit != "" && mark != "" && ui->tableWidget->item(i, 3)->checkState() == Qt::Checked)
        {
            sum_credit += credit.toFloat();
            sum_mark += credit.toFloat() * mark.toFloat();
            sum_point += credit.toFloat() * point_compute(mark.toInt());
        }
    }
    if (sum_credit == 0)
    {
        ui->lineEdit_2->setText("");
        ui->lineEdit_4->setText("");
    }
    else
    {
        ui->lineEdit_2->setText(QString("%1").arg(sum_mark / sum_credit));
        ui->lineEdit_4->setText(QString("%1").arg(sum_point / sum_credit));
    }
}

void MainWindow::clicked_allcheck()
{
    ui->tableWidget->blockSignals(true);
    if (ui->tableWidget->item(0, 3)->checkState() == Qt::Unchecked)
    {
        for (int i = 1; i < ui->tableWidget->rowCount() - 1; i++)
            ui->tableWidget->item(i, 3)->setCheckState(Qt::Unchecked);
    }
    else if (ui->tableWidget->item(0, 3)->checkState() == Qt::Checked)
    {
        for (int i = 1; i < ui->tableWidget->rowCount() - 1; i++)
            ui->tableWidget->item(i, 3)->setCheckState(Qt::Checked);
    }
    ui->tableWidget->blockSignals(false);
}

void MainWindow::change_allcheck()
{
    bool all_check = true, all_uncheck = true;
    for (int i = 1; i < ui->tableWidget->rowCount() - 1; i++)
    {
        if (ui->tableWidget->item(i, 3)->checkState() == Qt::Checked)
            all_uncheck = false;
        if (ui->tableWidget->item(i, 3)->checkState() == Qt::Unchecked)
            all_check = false;
    }
    if (all_check == false && all_uncheck == false)
        ui->tableWidget->item(0, 3)->setCheckState(Qt::PartiallyChecked);
    else if (all_check == false && all_uncheck == true)
        ui->tableWidget->item(0, 3)->setCheckState(Qt::Unchecked);
    else if (all_check == true && all_uncheck == false)
        ui->tableWidget->item(0, 3)->setCheckState(Qt::Checked);
    else
        ui->tableWidget->item(0, 3)->setCheckState(Qt::Checked);
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if (column != 0)
    {
        if (column == 3)
        {
            if (row == 0)
            {
                clicked_allcheck();
                change_allcheck();
            }
            else
                change_allcheck();
        }

        change_score();
    }
}

void MainWindow::Connections()
{
    // 关于
    connect(ui->action_about, &QAction::triggered, [this] {QMessageBox::information(this, tr("关于"),
            tr("shenzu "
               "Welcomed to use "
               "email: shenzu@mail.nwpu.edu.cn"));
                                                          });
    // 关于QT
    connect(ui->action_qt, &QAction::triggered, [this] {QMessageBox::aboutQt(this);});

    // 帮助
    connect(ui->action_help, &QAction::triggered, help_dialog, &QWidget::show);

    // 关闭程序
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::close);

    // 保存打开文件（接收内容显示框）
    connect(ui->action_open_file, &QAction::triggered, this, &MainWindow::open_file);
    connect(ui->action_save_file, &QAction::triggered, this, &MainWindow::save_as);

    // 绩点变化
    connect(ui->action_point, &QAction::triggered, point_transform, &QWidget::show);

    // 绩点变化同时刷新数据
    connect(point_transform, &PointTransform::close_signal, this, &MainWindow::change_score);
}

void MainWindow::closeEvent (QCloseEvent * )
{
    close();
}

void MainWindow::close()
{
    QFile file("temp_message");
    if (file.open(QFile::WriteOnly))
    {
        QTextStream stream(&file);
        for (int i = 1; i < ui->tableWidget->rowCount(); i++)
        {
            if (ui->tableWidget->item(i, 0)->text() == "" && ui->tableWidget->item(i, 1)->text() == "" && ui->tableWidget->item(i, 2)->text() == "")
                continue;
            stream << ui->tableWidget->item(i, 0)->text() << ' ' << ui->tableWidget->item(i, 1)->text() << ' '
                   << ui->tableWidget->item(i, 2)->text() << ' ' << ui->tableWidget->item(i, 3)->checkState() << endl;
        }
        file.close();
    }
    QWidget::close();
}

void MainWindow::open_file()
{
    // 加载文件至接收内容显示框
    QString filename = QFileDialog::getOpenFileName(this, tr("打开"));
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        statusBar()->showMessage("Open file failed", 5000);
        return;
    }
    QTextStream stream(&file);
    for (int i = 1; !stream.atEnd(); i++)
    {
        QStringList sl = stream.readLine().split(' ');
        ui->tableWidget->item(i, 0)->setText(sl[0]);
        ui->tableWidget->item(i, 1)->setText(sl[1]);
        ui->tableWidget->item(i, 2)->setText(sl[2]);
        ui->tableWidget->item(i, 3)->setCheckState(sl[3] == '0' ? Qt::Unchecked : Qt::Checked);
    }

    file.close();
}

void MainWindow::save_as()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("保存"));
    QFile file(filename);
    if (!file.open(QFile::WriteOnly))
    {
        statusBar()->showMessage("Save file failed", 5000);
        return;
    }

    QTextStream stream(&file);
    for (int i = 1; i < ui->tableWidget->rowCount(); i++)
    {
        if (ui->tableWidget->item(i, 0)->text() == "" && ui->tableWidget->item(i, 1)->text() == "" && ui->tableWidget->item(i, 2)->text() == "")
            continue;
        stream << ui->tableWidget->item(i, 0)->text() << ' ' << ui->tableWidget->item(i, 1)->text() << ' '
               << ui->tableWidget->item(i, 2)->text() << ' ' << ui->tableWidget->item(i, 3)->checkState() << endl;
    }
    file.close();
}
