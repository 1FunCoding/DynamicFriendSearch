#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

// Forward declaration for Network
class Network;

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();
    void onLoginButtonClicked();
    void showProfile(User* user);
    void displayFriendList(User* user);
    void navigateToFriendProfile(const std::string& friendName);
    void displayFriendSuggest(User* user);
    void friendclicked(int,int);
    void performSearch();
    void updateSearchResults();
    void onSearchListItemClicked(const QModelIndex &index);
private:
    Ui::SocialNetworkWindow *ui;
    Network* network;
    User* originalUser;
};
#endif // SOCIALNETWORKWINDOW_H
