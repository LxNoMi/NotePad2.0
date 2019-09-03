#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QWidget>
#include <QList>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QColor>
#include <QFont>
#include <QColorDialog>
#include <QFontDialog>
#include <QDesktopServices>
#include <QPalette>
#include <QInputDialog>
#include <QDateTime>
#include <QTimer>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init(void);

private slots:
    void New_Edit(void);
    void File_Open(void);
    void Del_Tab(int);
    void File_Save(void);
    void Unreal_Fun(void);
    void Set_Color(void);
    void Set_Font(void);
    void GO_Csdn(void);
    void About(void);
    void Click(int);
    void Find(void);
    void Zoom(void);
    void Flush_time(void);
    void Date_time(void);
private:
    //menu
    QMenu *file;
    QMenu *edit;
    QMenu *format;
    QMenu *view;
    QMenu *help;
    //向每个menu添加action     //文件
    QAction *file_new;
    QAction *file_open;
    QAction *file_save;
    QAction *file_saveas;
    QAction *file_pset;
    QAction *file_print;
    QAction *file_exit;

    //编辑
    QAction *edit_undo;
    QAction *edit_cut;
    QAction *edit_copy;
    QAction *edit_past;
    QAction *edit_del;
    QAction *edit_bing;
    QAction *edit_find;
    QAction *edit_find_n;
    QAction *edit_replace;
    QAction *edit_goto;
    QAction *edit_all;
    QAction *edit_date;

    //格式
    QAction *form_autoline;
    QAction *form_font;
    QAction *form_color;

    //查看
    QAction *view_zoom;
    QAction *view_status;

    //帮助
    QAction *help_csdn;
    QAction *help_about;


    //建立toolBar
    QToolBar *tbar;

    //statusbar
    QStatusBar *stbar;
    QLabel *lb_fileinfo;
    QLabel *lb_time;
    QLabel *lab_tmp;
    QLabel *lab_tmp1;

    QTabWidget *TW;

    //定义QList容器
    QList<QTextEdit*> Lst;

    //textedit ID
    int ID;
    QString filename;

    //状态栏显示时间
    QDateTime myTime;
    QTimer *timer;




};

#endif // MAINWINDOW_H
