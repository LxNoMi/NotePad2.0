#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗口属性
    this->setMinimumSize(640, 480);
    this->setWindowIcon(QIcon("D:/picture/icon/icon.png"));
    this->setWindowTitle("NotePad");

    Init();
    this->New_Edit();

    //connect
    connect(this->file_new, SIGNAL(triggered(bool)), this, SLOT(New_Edit()));//新建文件
    connect(this->file_open, SIGNAL(triggered(bool)), this, SLOT(File_Open()));//打开文件
    connect(this->TW, SIGNAL(tabCloseRequested(int)), this, SLOT(Del_Tab(int)));//删除tab
    connect(this->TW, SIGNAL(tabBarClicked(int)), this, SLOT(Click(int)));//定位点击位置
    connect(this->file_save, SIGNAL(triggered(bool)), this, SLOT(File_Save())); //保存文件
    connect(this->file_saveas, SIGNAL(triggered(bool)), this, SLOT(File_Save()));//另存为
    connect(this->file_exit, SIGNAL(triggered(bool)), this, SLOT(close()));//退出程序
    connect(this->file_pset, SIGNAL(triggered(bool)), this, SLOT(Unreal_Fun()));//页面设置
    connect(this->file_print, SIGNAL(triggered(bool)), this, SLOT(Unreal_Fun()));//打印
    connect(this->edit_undo, SIGNAL(triggered(bool)), this->Lst.at(this->TW->currentIndex()), SLOT(undo()));//撤销
    connect(this->edit_cut, SIGNAL(triggered(bool)), this->Lst.at(this->TW->currentIndex()), SLOT(cut()));//剪切
    connect(this->edit_copy, SIGNAL(triggered(bool)), this->Lst.at(this->TW->currentIndex()), SLOT(copy()));//复制
    connect(this->edit_past, SIGNAL(triggered(bool)), this->Lst.at(this->TW->currentIndex()), SLOT(paste()));//粘贴
    connect(this->edit_del, SIGNAL(triggered(bool)), this->Lst.at(this->TW->currentIndex()), SLOT(clear()));//清空
    connect(this->edit_all, SIGNAL(triggered(bool)), this->Lst.at(this->TW->currentIndex()), SLOT(selectAll()));//全选
    connect(this->edit_find, SIGNAL(triggered(bool)), this, SLOT(Find()));//查找
    connect(this->edit_find_n, SIGNAL(triggered(bool)), this, SLOT(Find()));//查找下一个
    connect(this->form_font, SIGNAL(triggered(bool)), this, SLOT(Set_Font()));//设置字体
    connect(this->form_color, SIGNAL(triggered(bool)), this, SLOT(Set_Color()));//设置颜色
    connect(this->form_autoline, SIGNAL(triggered(bool)), this, SLOT(Unreal_Fun()));//自动换行
    connect(this->help_csdn, SIGNAL(triggered(bool)), this, SLOT(GO_Csdn()));//转csdn技术支持
    connect(this->help_about, SIGNAL(triggered(bool)), this, SLOT(About()));//关于
    connect(this->view_zoom, SIGNAL(triggered(bool)), this, SLOT(Zoom()));//缩小
    connect(this->timer, SIGNAL(timeout()), this, SLOT(Flush_time()));//刷新时间
    connect(this->edit_date, SIGNAL(triggered(bool)), this, SLOT(Date_time()));//插入时间日期


}

MainWindow::~MainWindow()
{

}

void MainWindow::Init()
{
    //添加menu
    file = menuBar()->addMenu("文件(&F)");
    edit = menuBar()->addMenu("编辑(&E)");
    format = menuBar()->addMenu("格式(&O)");
    view = menuBar()->addMenu("查看(&V)");
    help = menuBar()->addMenu("帮助(&H)");

    //向每个menu添加action     //文件
    file_new = new QAction(QIcon(":/icon/file_new.png"), "新建(&N)");
    file_open = new QAction(QIcon(":/icon/file_open.png"), "打开(&O)");
    file_save = new QAction(QIcon(":/icon/file_save.png"), "保存(&S)");
    file_saveas = new QAction(QIcon(":/icon/file_saveas.png"), "另存为(&N)");
    file_pset = new QAction(QIcon(":/icon/file_pset.png"), "页面设置(&N)");
    file_print = new QAction(QIcon(":/icon/file_print.png"), "打印(&P)");
    file_exit = new QAction(QIcon(":/icon/file_exit.png"), "退出(&X)");
    file->addAction(file_new);
    file->addAction(file_open);
    file->addAction(file_save);
    file->addAction(file_saveas);
    file->addSeparator();
    file->addAction(file_pset);
    file->addAction(file_print);
    file->addSeparator();
    file->addAction(file_exit);

    //编辑
    edit_undo = new QAction(QIcon(":/icon/edit_undo.png"), "撤销(&U)");
    edit_cut = new QAction(QIcon(":/icon/edit_cut.png/"), "剪切(&T)");
    edit_copy = new QAction(QIcon(":/icon/edit_copy.png"), "复制(&C)");
    edit_past = new QAction(QIcon(":/icon/edit_past.png"), "粘贴(&P");
    edit_del = new QAction(QIcon(":/icon/edit_del.png"), "清空(&L)");
    edit_bing = new QAction(QIcon(":/icon/edit_bing.png"), "使用bing搜素");
    edit_find = new QAction(QIcon(":/icon/edit_find.png"), "查找(&F)");
    edit_find_n = new QAction(QIcon(":/icon/edit_find_n.png"), "查找下一个(&N)");
    edit_replace = new QAction(QIcon(":/icon/edit_replace.png"), "替换(&R)");
    edit_goto = new QAction(QIcon(":/icon/edit_goto.png"), "转到(&G)");
    edit_all = new QAction(QIcon(":/icon/edit_all.png"), "全选(&A)");
    edit_date = new QAction(QIcon(":/icon/edit_date.png"), "时间/日期(&D)");
    edit->addAction(edit_undo);
    edit->addAction(edit_cut);
    edit->addAction(edit_copy);
    edit->addAction(edit_past);
    edit->addAction(edit_del);
    edit->addAction(edit_bing);
    edit->addAction(edit_find);
    edit->addAction(edit_find_n);
    edit->addAction(edit_replace);
    edit->addAction(edit_goto);
    edit->addAction(edit_all);
    edit->addAction(edit_date);

    //格式
    form_autoline = new QAction(QIcon(":/icon/form_autoline.png"), "自动换行");
    form_font = new QAction(QIcon(":/icon/form_font.png"), "字体");
    form_color = new QAction(QIcon(":/icon/form_color.png"), "颜色");
    format->addAction(form_autoline);
    format->addAction(form_font);
    format->addAction(form_color);

    //查看
    view_zoom = new QAction(QIcon(":/icon/view_zoom.png"), "缩放");
    view_status= new QAction(QIcon(":/icon/view_status.png"), "状态栏");
    view->addAction(view_zoom);
    view->addAction(view_status);

    //帮助
    help_csdn = new QAction(QIcon(":/icon/help_csdn.png"), "CSDN技术支持");
    help_about = new QAction(QIcon(":/icon/help_about.png"), "关于");
    help->addAction(help_csdn);
    help->addSeparator();
    help->addAction(help_about);


    //建立toolBar
    tbar = addToolBar("文件");
    tbar->addAction(file_open);
    tbar->addAction(file_save);
    tbar->addSeparator();
    tbar->addAction(edit_undo);
    tbar->addAction(edit_cut);
    tbar->addAction(edit_copy);
    tbar->addAction(edit_past);
    tbar->addAction(edit_del);
    tbar->addAction(edit_find);
    tbar->addAction(edit_all);
    tbar->addSeparator();
    tbar->addAction(form_font);
    tbar->addAction(form_color);

    //tabwidget
    this->TW = new QTabWidget(this);
    this->setCentralWidget(TW);

    //statusbar
    this->stbar = statusBar();
    this->lb_fileinfo = new QLabel();
    this->lb_time = new QLabel();
    stbar->addWidget(lb_fileinfo);
    this->lab_tmp = new QLabel("                          ");
    this->lab_tmp1 = new QLabel("                          ");
    stbar->addWidget(lab_tmp);
    stbar->addWidget(lab_tmp1);
    stbar->addWidget(lb_time);

    this->ID = 0;
    this->filename = "未命名";
    this->Flush_time();
    this->timer = new QTimer(this);
    timer->start(1000);
}

void MainWindow::New_Edit()
{
    QTextEdit *te = new QTextEdit();
    this->Lst.append(te);

    this->TW->addTab(Lst.at(ID), filename);
    this->lb_fileinfo->setText(filename);
    this->ID++;
    this->filename = "未命名";
    TW->setTabsClosable(1);
    //connect(this->TW, SIGNAL(tabCloseRequested(int)),TW ,SLOT(Del_Tab()));
}

void MainWindow::File_Open()
{
    qDebug()<<"打开文件";
    QString Fname;
    Fname = QFileDialog::getOpenFileName(this, "打开文件", "./");
    if(Fname.isEmpty()){
        QMessageBox::information(this, "警告", "文件打开失败");
        return;
    }
    qDebug()<<"打开文件成功";

    QFile file(Fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(this, "警告", "文件读取失败");
        return;
    }

    //建立edit装内容
    QFileInfo fileinfo(Fname);
    filename = fileinfo.fileName();
    this->New_Edit();
    this->TW->setCurrentIndex(ID-1);

    //读取
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        this->Lst.at(ID-1)->append(line);
    }
    file.close();
    qDebug()<<"读取文件成功";
}

void MainWindow::Del_Tab(int index)
{
    TW->removeTab(index);
}

void MainWindow::File_Save()
{
    QString sFname = QFileDialog::getOpenFileName(this, "保存文件", "./");
    if(sFname.isEmpty()){
        QMessageBox::information(this, "错误提示", "文件保存失败");
        return;
    }

    //进行写操作
    QString txt = this->Lst.at(this->TW->currentIndex())->toPlainText();
    QFile file(sFname);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.write(txt.toUtf8());
    file.close();
    QMessageBox::information(this, "错误提示", "文件保存成功");
}

void MainWindow::Unreal_Fun()
{
    QMessageBox::information(this, "温馨提示", "无效设置模式...");
    return;
}

void MainWindow::Set_Color()
{
    QColor mycolor = QColorDialog::getColor();
    this->Lst.at(TW->currentIndex())->setTextColor(mycolor);
    if(mycolor.isValid()){
        QMessageBox::information(this, "提示", "颜色获取失败");
        return;
    }
}

void MainWindow::Set_Font()
{
    bool ok;
    QFont myfont = QFontDialog::getFont(&ok);
    if(ok)
    {
        this->Lst.at(TW->currentIndex())->setFont(myfont);
    }
    else
    {
        QMessageBox::information(this, "提示", "字体设置失败");
        return;
    }
}

void MainWindow::GO_Csdn()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://blog.csdn.net/qq_38853493")));
    return;
}

void MainWindow::About()
{
    QMessageBox::about(this, "关于记事本", "软件名：NotePad记事本\n版本号:2.1.0版本\n技术支持：Qt、CSDN个人博客\n版权所有:地球村科技有限公司\n版权所有者：NoMi(刘讯)");
    return;
}

void MainWindow::Click(int index)
{
    this->TW->setCurrentIndex(index);
    this->lb_fileinfo->setText("文件名："+TW->tabText(index));
}

void MainWindow::Find()
{
    QString txt = QInputDialog::getText(this, "文本查找", "匹配内容:");
    if (!this->Lst.at(TW->currentIndex())->find(txt, QTextDocument::FindBackward))
    {
       QMessageBox::warning(this, tr("查找"),
                tr("找不到%1").arg(txt));
    }
}

void MainWindow::Zoom()
{
    this->Lst.at(TW->currentIndex())->setFont(QFont(tr("Consolas"), 14));
}

void MainWindow::Flush_time()
{
    this->myTime = QDateTime::currentDateTime();
    QString str = this->myTime.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    this->lb_time->setText("                 当前时间: "+str);//在标签上显示时间
}

void MainWindow::Date_time()
{
    QString str = this->myTime.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    this->Lst.at(TW->currentIndex())->append(str);
    return;
}
