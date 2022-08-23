#include "helpdialog.h"
/*
 * HelpDialog类构造函数
 * 显示帮助信息
 */
HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
{
    layout = new QGridLayout(this);
    text = new QTextBrowser();
    layout->addWidget(text);
    text->setText("使用帮助\n"
                  "\n"
                  "一、添加课程成绩\n"
                  "  1.课程："
                  "      课程的名称（可不填）\n"
                  "  2.学分：\n"
                  "      此课程对应的学分（可不为整数）\n"
                  "  3.成绩：\n"
                  "      此课程对应的成绩（绩点转换范围内）\n"
                  "  4.全选：\n"
                  "      当选择第一行的全选，所有课程都会选中，再次点击，则所有课程都未选中。\n"
                  "      当选择非第一行，则代表此行课程被选中，再次点击，则此课程未选中。\n"
                  "      当第一行全选按钮显示对勾时，代表全部课程选中；显示方块，代表部分课程选中；显示空，代表全部课程未选中。\n"
                  "      当非第一行按钮显示对勾时，代表课程选中；显示空，代表课程未选中。\n"
                  "\n"
                  "二、绩点转换\n"
                  "  1.成绩范围：\n"
                  "      在两个空格内填入成绩的范围（顺序无要求）。\n"
                  "  2.绩点：\n"
                  "      在空格内填入此成绩范围内对应的绩点。\n"
                  "  3.更新：\n"
                  "      关闭“绩点转换”窗口，自动更新数据。\n"
                  "\n"
                  "三、数据保存于加载\n"
                  "  1.数据保存：\n"
                  "      当想要保存此页数据，并等待下次加载\n"
                  "  2.数据加载：\n"
                  "      当想要加载保存的数据\n"
                  "\n");
    resize(800, 520);
    setWindowFlags(Qt::Window);
    setWindowTitle(tr("帮助"));
}

HelpDialog::~HelpDialog()
{
}

