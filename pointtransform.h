#ifndef POINTTRANSFORM_H
#define POINTTRANSFORM_H

#include <QDialog>
#include <QLineEdit>

namespace Ui
{
class PointTransform;
}

class PointTransform : public QDialog
{
    Q_OBJECT

public:
    explicit PointTransform(QWidget *parent = nullptr);
    ~PointTransform();

    void point_range_refresh();

    typedef struct
    {
        QPair<int, int> range;
        float point;
    } PointRange;
    QVector<PointRange> point_range;

signals:
    void close_signal();

private slots:
    void closeEvent (QCloseEvent * );

private:
    Ui::PointTransform *ui;

    QVector<QVector<QLineEdit*>> line_edit;
};

#endif // POINTTRANSFORM_H
