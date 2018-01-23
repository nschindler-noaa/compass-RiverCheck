/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 22 12:49:24 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_File_Open;
    QAction *action_File_Save;
    QAction *action_File_Save_As;
    QAction *action_File_Print;
    QAction *action_File_Exit;
    QAction *action_Help_About;
    QAction *action_Help_About_Qt;
    QAction *action_File_Revert_to_Saved;
    QAction *actionShow_File_Header;
    QAction *actionShow_Map;
    QAction *actionShow_Current_Dam;
    QAction *actionShow_Current_Reach;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_map;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_info;
    QLabel *label_spacer;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLabel *RiverSystemName;
    QGraphicsView *mapView;
    QWidget *page_dam;
    QVBoxLayout *verticalLayout_3;
    QLabel *DamName;
    QHBoxLayout *horizontalLayout_damPage;
    QWidget *page_reach;
    QVBoxLayout *verticalLayout_2;
    QLabel *ReachName;
    QHBoxLayout *horizontalLayout_reachPage;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QMenu *menu;
    QMenu *menu_Edit;
    QMenu *menu_View;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(696, 536);
        action_File_Open = new QAction(MainWindow);
        action_File_Open->setObjectName(QString::fromUtf8("action_File_Open"));
        action_File_Save = new QAction(MainWindow);
        action_File_Save->setObjectName(QString::fromUtf8("action_File_Save"));
        action_File_Save_As = new QAction(MainWindow);
        action_File_Save_As->setObjectName(QString::fromUtf8("action_File_Save_As"));
        action_File_Print = new QAction(MainWindow);
        action_File_Print->setObjectName(QString::fromUtf8("action_File_Print"));
        action_File_Exit = new QAction(MainWindow);
        action_File_Exit->setObjectName(QString::fromUtf8("action_File_Exit"));
        action_Help_About = new QAction(MainWindow);
        action_Help_About->setObjectName(QString::fromUtf8("action_Help_About"));
        action_Help_About_Qt = new QAction(MainWindow);
        action_Help_About_Qt->setObjectName(QString::fromUtf8("action_Help_About_Qt"));
        action_File_Revert_to_Saved = new QAction(MainWindow);
        action_File_Revert_to_Saved->setObjectName(QString::fromUtf8("action_File_Revert_to_Saved"));
        actionShow_File_Header = new QAction(MainWindow);
        actionShow_File_Header->setObjectName(QString::fromUtf8("actionShow_File_Header"));
        actionShow_Map = new QAction(MainWindow);
        actionShow_Map->setObjectName(QString::fromUtf8("actionShow_Map"));
        actionShow_Current_Dam = new QAction(MainWindow);
        actionShow_Current_Dam->setObjectName(QString::fromUtf8("actionShow_Current_Dam"));
        actionShow_Current_Reach = new QAction(MainWindow);
        actionShow_Current_Reach->setObjectName(QString::fromUtf8("actionShow_Current_Reach"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_map = new QWidget();
        page_map->setObjectName(QString::fromUtf8("page_map"));
        horizontalLayout_2 = new QHBoxLayout(page_map);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_info = new QVBoxLayout();
        verticalLayout_info->setSpacing(6);
        verticalLayout_info->setObjectName(QString::fromUtf8("verticalLayout_info"));
        label_spacer = new QLabel(page_map);
        label_spacer->setObjectName(QString::fromUtf8("label_spacer"));

        verticalLayout_info->addWidget(label_spacer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_info->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_info);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        RiverSystemName = new QLabel(page_map);
        RiverSystemName->setObjectName(QString::fromUtf8("RiverSystemName"));
        RiverSystemName->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(RiverSystemName);

        mapView = new QGraphicsView(page_map);
        mapView->setObjectName(QString::fromUtf8("mapView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapView->sizePolicy().hasHeightForWidth());
        mapView->setSizePolicy(sizePolicy);
        mapView->setMinimumSize(QSize(300, 200));

        verticalLayout_4->addWidget(mapView);


        horizontalLayout_2->addLayout(verticalLayout_4);

        stackedWidget->addWidget(page_map);
        page_dam = new QWidget();
        page_dam->setObjectName(QString::fromUtf8("page_dam"));
        verticalLayout_3 = new QVBoxLayout(page_dam);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        DamName = new QLabel(page_dam);
        DamName->setObjectName(QString::fromUtf8("DamName"));
        DamName->setMaximumSize(QSize(16777215, 20));
        DamName->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(DamName);

        horizontalLayout_damPage = new QHBoxLayout();
        horizontalLayout_damPage->setSpacing(6);
        horizontalLayout_damPage->setObjectName(QString::fromUtf8("horizontalLayout_damPage"));

        verticalLayout_3->addLayout(horizontalLayout_damPage);

        stackedWidget->addWidget(page_dam);
        page_reach = new QWidget();
        page_reach->setObjectName(QString::fromUtf8("page_reach"));
        verticalLayout_2 = new QVBoxLayout(page_reach);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ReachName = new QLabel(page_reach);
        ReachName->setObjectName(QString::fromUtf8("ReachName"));
        ReachName->setMaximumSize(QSize(16777215, 20));
        ReachName->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(ReachName);

        horizontalLayout_reachPage = new QHBoxLayout();
        horizontalLayout_reachPage->setSpacing(6);
        horizontalLayout_reachPage->setObjectName(QString::fromUtf8("horizontalLayout_reachPage"));

        verticalLayout_2->addLayout(horizontalLayout_reachPage);

        stackedWidget->addWidget(page_reach);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 696, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_File_Open);
        menu_File->addAction(action_File_Save);
        menu_File->addAction(action_File_Save_As);
        menu_File->addAction(action_File_Revert_to_Saved);
        menu_File->addSeparator();
        menu_File->addAction(action_File_Print);
        menu_File->addSeparator();
        menu_File->addAction(action_File_Exit);
        menu_Help->addAction(action_Help_About);
        menu_Help->addSeparator();
        menu_Help->addAction(action_Help_About_Qt);
        menu_Edit->addAction(actionShow_File_Header);
        menu_View->addAction(actionShow_Map);
        menu_View->addAction(actionShow_Current_Dam);
        menu_View->addAction(actionShow_Current_Reach);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        action_File_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
#ifndef QT_NO_TOOLTIP
        action_File_Open->setToolTip(QApplication::translate("MainWindow", "Open a river description file", 0));
#endif // QT_NO_TOOLTIP
        action_File_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        action_File_Save->setText(QApplication::translate("MainWindow", "&Save", 0));
#ifndef QT_NO_TOOLTIP
        action_File_Save->setToolTip(QApplication::translate("MainWindow", "Save the current file", 0));
#endif // QT_NO_TOOLTIP
        action_File_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        action_File_Save_As->setText(QApplication::translate("MainWindow", "Save &As ...", 0));
#ifndef QT_NO_TOOLTIP
        action_File_Save_As->setToolTip(QApplication::translate("MainWindow", "Save current file as a new file", 0));
#endif // QT_NO_TOOLTIP
        action_File_Print->setText(QApplication::translate("MainWindow", "&Print ...", 0));
#ifndef QT_NO_TOOLTIP
        action_File_Print->setToolTip(QApplication::translate("MainWindow", "Print the current file", 0));
#endif // QT_NO_TOOLTIP
        action_File_Print->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        action_File_Exit->setText(QApplication::translate("MainWindow", "E&xit", 0));
#ifndef QT_NO_TOOLTIP
        action_File_Exit->setToolTip(QApplication::translate("MainWindow", "Leave the application", 0));
#endif // QT_NO_TOOLTIP
        action_File_Exit->setShortcut(QApplication::translate("MainWindow", "Alt+Q", 0));
        action_Help_About->setText(QApplication::translate("MainWindow", "&About", 0));
#ifndef QT_NO_TOOLTIP
        action_Help_About->setToolTip(QApplication::translate("MainWindow", "Information about this application", 0));
#endif // QT_NO_TOOLTIP
        action_Help_About_Qt->setText(QApplication::translate("MainWindow", "About &Qt", 0));
#ifndef QT_NO_TOOLTIP
        action_Help_About_Qt->setToolTip(QApplication::translate("MainWindow", "Information about the version of Qt used to produce this application.", 0));
#endif // QT_NO_TOOLTIP
        action_File_Revert_to_Saved->setText(QApplication::translate("MainWindow", "&Revert to Saved", 0));
#ifndef QT_NO_TOOLTIP
        action_File_Revert_to_Saved->setToolTip(QApplication::translate("MainWindow", "Discard any edits and revert to saved data.", 0));
#endif // QT_NO_TOOLTIP
        actionShow_File_Header->setText(QApplication::translate("MainWindow", "Edit File &Header", 0));
        actionShow_File_Header->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0));
        actionShow_Map->setText(QApplication::translate("MainWindow", "Show &Map", 0));
        actionShow_Current_Dam->setText(QApplication::translate("MainWindow", "Show Current &Dam", 0));
        actionShow_Current_Reach->setText(QApplication::translate("MainWindow", "Show Current &Reach", 0));
        label_spacer->setText(QString());
        RiverSystemName->setText(QApplication::translate("MainWindow", "River System Name", 0));
        DamName->setText(QApplication::translate("MainWindow", "Dam Name", 0));
        ReachName->setText(QApplication::translate("MainWindow", "Reach Name", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0));
        menu->setTitle(QString());
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
