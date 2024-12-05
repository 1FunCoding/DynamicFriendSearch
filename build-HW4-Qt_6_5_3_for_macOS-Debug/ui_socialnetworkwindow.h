/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLabel *myProfile;
    QLabel *personProfile;
    QTableWidget *myList;
    QLabel *FriendLabel;
    QLabel *Suggestion;
    QLabel *FiveRecentPost;
    QTableWidget *friendSuggestion;
    QLabel *recentPost;
    QPushButton *returnOrigin;
    QPushButton *addFriendButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 20, 231, 16));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 60, 201, 41));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 120, 161, 41));
        myProfile = new QLabel(centralwidget);
        myProfile->setObjectName("myProfile");
        myProfile->setGeometry(QRect(410, 0, 71, 16));
        personProfile = new QLabel(centralwidget);
        personProfile->setObjectName("personProfile");
        personProfile->setGeometry(QRect(390, 20, 171, 16));
        myList = new QTableWidget(centralwidget);
        myList->setObjectName("myList");
        myList->setGeometry(QRect(233, 70, 271, 161));
        FriendLabel = new QLabel(centralwidget);
        FriendLabel->setObjectName("FriendLabel");
        FriendLabel->setGeometry(QRect(333, 50, 111, 16));
        Suggestion = new QLabel(centralwidget);
        Suggestion->setObjectName("Suggestion");
        Suggestion->setGeometry(QRect(613, 50, 131, 16));
        FiveRecentPost = new QLabel(centralwidget);
        FiveRecentPost->setObjectName("FiveRecentPost");
        FiveRecentPost->setGeometry(QRect(450, 240, 171, 16));
        friendSuggestion = new QTableWidget(centralwidget);
        friendSuggestion->setObjectName("friendSuggestion");
        friendSuggestion->setGeometry(QRect(533, 70, 271, 161));
        recentPost = new QLabel(centralwidget);
        recentPost->setObjectName("recentPost");
        recentPost->setGeometry(QRect(270, 260, 521, 191));
        returnOrigin = new QPushButton(centralwidget);
        returnOrigin->setObjectName("returnOrigin");
        returnOrigin->setGeometry(QRect(580, 0, 181, 32));
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(90, 180, 100, 32));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        label->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your name:", nullptr));
        pushButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        myProfile->setText(QCoreApplication::translate("SocialNetworkWindow", "My Profile", nullptr));
        personProfile->setText(QCoreApplication::translate("SocialNetworkWindow", "Person's Name Profile", nullptr));
        FriendLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "FriendsList", nullptr));
        Suggestion->setText(QCoreApplication::translate("SocialNetworkWindow", "Friends Suggestion", nullptr));
        FiveRecentPost->setText(QCoreApplication::translate("SocialNetworkWindow", "Five Recent Posts", nullptr));
        recentPost->setText(QString());
        returnOrigin->setText(QCoreApplication::translate("SocialNetworkWindow", "return to", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Friend", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
