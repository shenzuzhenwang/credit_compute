#include "pointtransform.h"
#include "ui_pointtransform.h"

PointTransform::PointTransform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PointTransform)
{
    ui->setupUi(this);
    QVector<QLineEdit*> temp = {ui->lineEdit_1, ui->lineEdit_2, ui->lineEdit_3};
    line_edit.append(temp);
    temp = {ui->lineEdit_4, ui->lineEdit_5, ui->lineEdit_6};
    line_edit.append(temp);
    temp = {ui->lineEdit_7, ui->lineEdit_8, ui->lineEdit_9};
    line_edit.append(temp);
    temp = {ui->lineEdit_10, ui->lineEdit_11, ui->lineEdit_12};
    line_edit.append(temp);
    temp = {ui->lineEdit_13, ui->lineEdit_14, ui->lineEdit_15};
    line_edit.append(temp);
    temp = {ui->lineEdit_16, ui->lineEdit_17, ui->lineEdit_18};
    line_edit.append(temp);
    temp = {ui->lineEdit_19, ui->lineEdit_20, ui->lineEdit_21};
    line_edit.append(temp);
    temp = {ui->lineEdit_22, ui->lineEdit_23, ui->lineEdit_24};
    line_edit.append(temp);
    temp = {ui->lineEdit_25, ui->lineEdit_26, ui->lineEdit_27};
    line_edit.append(temp);
    temp = {ui->lineEdit_28, ui->lineEdit_29, ui->lineEdit_30};
    line_edit.append(temp);
    temp = {ui->lineEdit_31, ui->lineEdit_32, ui->lineEdit_33};
    line_edit.append(temp);
    temp = {ui->lineEdit_34, ui->lineEdit_35, ui->lineEdit_36};
    line_edit.append(temp);
    temp = {ui->lineEdit_37, ui->lineEdit_38, ui->lineEdit_39};
    line_edit.append(temp);
    temp = {ui->lineEdit_40, ui->lineEdit_41, ui->lineEdit_42};
    line_edit.append(temp);
    temp = {ui->lineEdit_43, ui->lineEdit_44, ui->lineEdit_45};
    line_edit.append(temp);

    point_range_refresh();
}

PointTransform::~PointTransform()
{
    delete ui;
}

void PointTransform::closeEvent (QCloseEvent * )
{
    point_range_refresh();
    emit close_signal();
}

void PointTransform::point_range_refresh()
{
    point_range.clear();
    point_range.squeeze();
    for (int i = 0; i < 15; i++)
    {
        if (line_edit[i][0]->text() != NULL && line_edit[i][1]->text() != NULL && line_edit[i][2]->text() != NULL)
        {
            PointRange temp;
            temp.range.first = std::max(line_edit[i][0]->text().toInt(), line_edit[i][1]->text().toInt());
            temp.range.second = std::min(line_edit[i][0]->text().toInt(), line_edit[i][1]->text().toInt());
            temp.point = line_edit[i][2]->text().toFloat();
            point_range.append(temp);
        }
    }
}
