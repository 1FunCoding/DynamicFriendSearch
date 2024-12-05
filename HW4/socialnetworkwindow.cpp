#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "network.h"
#include "user.h"
#include <QMessageBox>
#include <QDir>
#include <QStringListModel>



SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{

    ui->setupUi(this);
    network = new Network();  // Initialize the Network instance
    qDebug() << "Current Directory:" << QDir::currentPath();
    //the read file part does not work as intended
    char filename[] = "social_network.txt";
    int result = network->readUsers(filename);
    if (result == 0) {
        std::cout << "Users read from " << filename << " successfully." << std::endl;
    } else {
        std::cout << "Error: Failed to read users from " << filename << "." << std::endl;
    }
    std::cout<<network->numUsers()<<std::endl;


    char filename2[] = "posts.txt";
    int res = network->readPosts(filename2);
    if (res == 0) {
        std::cout << "Users read from " << filename2 << " successfully." << std::endl;
    } else {
        std::cout << "Error: Failed to read users from " << filename << "." << std::endl;
    }
    ui->myList->hide();
    ui->Suggestion->hide();
    ui->friendSuggestion->hide();
    ui->myProfile->hide();
    ui->personProfile->hide();
    ui->FriendLabel->hide();
    ui->Suggestion->hide();
    ui->FiveRecentPost->hide();
    ui->recentPost->hide();
    ui->returnOrigin->hide();
    ui->addFriendButton->hide();
    ui->searchBox->hide();
    ui->searchButton->hide();
    ui->searchList->hide();


    connect(ui->pushButton, &QPushButton::clicked, this, &SocialNetworkWindow::onLoginButtonClicked);
    connect(ui->friendSuggestion,&QTableWidget::cellClicked,this,&SocialNetworkWindow::friendclicked);
    connect(ui->searchBox, &QLineEdit::textChanged, this, &SocialNetworkWindow::updateSearchResults);
    connect(ui->searchButton, &QPushButton::clicked, this, &SocialNetworkWindow::performSearch);
    // Connect the clicked signal to the slot
    connect(ui->searchList, &QListView::clicked, this, &SocialNetworkWindow::onSearchListItemClicked);

    //debug code to test out getAllUserNames in network.cpp (newly implemented function).
    /*
    std::vector<std::string> allUserNames = network->getAllUserNames();
    std::cout << "All User Names:" << std::endl;
    for (const std::string& name : allUserNames) {
        std::cout << name << std::endl;
    }
    */

}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete network;  // Clean up the Network instance
    delete ui;
}

void SocialNetworkWindow::onLoginButtonClicked()
{

    QString enteredName = ui->textEdit->toPlainText().trimmed();
    QStringList nameParts = enteredName.split(' ');

    if (nameParts.size() < 2) {
        QMessageBox::warning(this, "Login Failed", "Please enter both first name and last name.");
        return;
    }

    QString firstName = nameParts.at(0);
    QString lastName = nameParts.at(1);

    std::string userName = (firstName + " " + lastName).toStdString();
    std::size_t id = network->getId(userName);
    originalUser = network->getUser(id);
    //std::cout<<originalUser->getId()<<std::endl;



    if(network->getUser(id) != nullptr)
    {
        QMessageBox::information(this, "Login Successful", "Welcome " + firstName + " " + lastName + "!");
        ui->label->hide();
        ui->textEdit->hide();
        ui->pushButton->hide();
        ui->myList->show();

        User* user = network->getUser(id);
        showProfile(user);

    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "The entered name doesn't exist. Please try again.");
    }

}


void SocialNetworkWindow::showProfile(User* user){
    std::string userName = user->getName();
    int numRecentPosts =5;

    // Prompt user for the name and number of recent posts
  //  std::cout << "Enter the username followed by the number of recent posts to display: "<<std::endl;


    // Fetch and display the posts using the Network::displayPosts method

   // std::cout<<network->displayPosts(userName, numRecentPosts)<<std::endl;

    ui->addFriendButton->show();
    if(user==originalUser){
        ui->myProfile->show();
        ui->personProfile->hide();
        ui->returnOrigin->hide();
    }
    if(user!=originalUser){
        ui->myProfile->hide();
        ui->personProfile->show();
        ui->personProfile->update();
        ui->returnOrigin->show();
        //std::cout<<originalUser->getName()<<std::endl;

    }
    ui->myList->show();
    ui->Suggestion->show();
    ui->friendSuggestion->show();
    ui->FriendLabel->show();
    ui->FiveRecentPost->show();
    ui->recentPost->show();
    ui->searchBox->show();
    ui->searchButton->show();

    //connect myProfile
    std::string posts = network->displayPosts(userName, 5);
    ui->recentPost->setText(QString::fromStdString(posts));

    std::string returnText = "return to " + originalUser->getName();
    ui->returnOrigin->setText(QString::fromStdString(returnText));


    connect(ui->returnOrigin, &QPushButton::clicked, this, [this]() {
        showProfile(originalUser);
    });

    displayFriendList(user);
    if(user==originalUser){
    displayFriendSuggest(user);
    }
     else{
    ui->friendSuggestion->clear();
    ui->friendSuggestion->setRowCount(0);
    ui->friendSuggestion->hide();
    ui->Suggestion->hide();

    }

    if(user != originalUser) {
    disconnect(ui->addFriendButton, &QPushButton::clicked, this, nullptr);
    connect(ui->addFriendButton, &QPushButton::clicked, this, [this, user]() {
        int temp = network->addConnection(originalUser->getName(), user->getName());
        std::cout << temp << std::endl;
        std::cout<<user->getName()<<std::endl;
        QMessageBox::information(this, "Friend Added", "You have added " + QString::fromStdString(user->getName()) + " as a friend.");
    });
    }



}
void SocialNetworkWindow::displayFriendSuggest(User *user) {
    if (!user) {
        QMessageBox::warning(this, "Error", "Invalid user.");
        return;
    }

    std::size_t score = 3; // To hold the score of suggestions
    std::vector<std::size_t> suggestedFriendIDs = network->suggestFriends(user->getId(), score);

    // Convert the suggested friend IDs to names
    std::vector<std::string> suggestedFriendNames;
    for (std::size_t id : suggestedFriendIDs) {
        User* suggestedUser = network->getUser(id);
        if (suggestedUser) { // Check if the user exists
            suggestedFriendNames.push_back(suggestedUser->getName());
        }
    }
   // std::cout<<suggestedFriendNames.size()<<std::endl;

    // Display the suggested friends in the friendSuggestion QTableWidget
    ui->friendSuggestion->setRowCount(suggestedFriendNames.size());
    ui->friendSuggestion->setColumnCount(2);
    for (size_t i = 0; i < suggestedFriendNames.size(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(suggestedFriendNames[i]));
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(std::to_string(score)));
        ui->friendSuggestion->setItem(i, 0, item);
        ui->friendSuggestion->setItem(i, 1, item2);
    }

}
void SocialNetworkWindow::displayFriendList(User* user) {
    // Retrieve the friend IDs for the given user
    std::vector<std::size_t> friendIDs = user->getFriends();

    // Set up the QTableWidget
    ui->myList->setRowCount(friendIDs.size());
    ui->myList->setColumnCount(1);  // Assuming you want 1 column for friend names

    // Populate the QTableWidget with friend names
    for (size_t i = 0; i < friendIDs.size(); i++) {
        User* friendUser = network->getUser(friendIDs[i]);
        std::string friendName = friendUser->getName();
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(friendName));
        ui->myList->setItem(i, 0, item);
    }

    // Disconnect any existing connections to ensure no multiple connections
    disconnect(ui->myList, &QTableWidget::cellClicked, this, nullptr);

    // Connect the cellClicked signal to navigate to friend's profile
    connect(ui->myList, &QTableWidget::cellClicked, this, [this](int row, int column) {
        Q_UNUSED(column);  // Column is not used
        std::string friendName = ui->myList->item(row, 0)->text().toStdString();
        navigateToFriendProfile(friendName);
    });
}



void SocialNetworkWindow::navigateToFriendProfile(const std::string& friendName) {
    size_t tempid = network->getId(friendName);
    User* friendtemp = network->getUser(tempid);
    showProfile(friendtemp);
    std::string userName = friendtemp->getName();
    std::string profileText = userName + "'s Profile";
    ui->personProfile->setText(QString::fromStdString(profileText));

}

void SocialNetworkWindow::friendclicked(int row,int col)
{
    QString Name= ui->friendSuggestion->item(row,col)->text();
    std::string tempname=Name.toStdString();
    User*temp=network->getUser(network->getId(tempname));
    std::string profileText = tempname + "'s Profile";
    ui->personProfile->setText(QString::fromStdString(profileText));

    showProfile(temp);

}

void SocialNetworkWindow::performSearch() {
    QString searchText = ui->searchBox->text().trimmed();
    if (searchText.isEmpty()) {
        QMessageBox::information(this, "Search Error", "Please enter a search query.");
        return;
    }

    // Use the Network object to search for the user ID
    std::size_t userId = network->getId(searchText.toStdString());

    if (userId != static_cast<std::size_t>(-1)) {
        // User found, retrieve and display the user's profile information
        User* user = network->getUser(userId);
        if (user) {
            // Assuming you have a method to display the user profile
            showProfile(user);
            std::string userName= user->getName();
            std::string profileText = userName + "'s Profile";
            ui->personProfile->setText(QString::fromStdString(profileText));
            ui->searchList->hide();

        }
    } else {
        // User not found, optionally handle this case
        QMessageBox::information(this, "User Not Found", "The user could not be found. Please try a different search query.");

    }
}

void SocialNetworkWindow::updateSearchResults() {
    QString text = ui->searchBox->text();

    //Create the searchListModel
    QStringListModel* searchListModel = new QStringListModel(this);
    ui->searchList->setModel(searchListModel);  // Assign the model to the QListView


    if (text.isEmpty()) {
        searchListModel->setStringList(QStringList());
        ui->searchList->hide();
    } else {
        // Fetch and convert all usernames to QStringList
        QStringList allUserNames;
        //New functionality in network.cpp to get All user names in the social_network.txt
        std::vector<std::string> names = network->getAllUserNames();
        for (const auto& name : names) {
            allUserNames << QString::fromStdString(name);
        }

        // Filter usernames that contain the input text
        QStringList filteredList = allUserNames.filter(text, Qt::CaseInsensitive);

        // Update the model with the filtered list
        searchListModel->setStringList(filteredList);

        // Show or hide the searchList based on whether there are filtered items
        ui->searchList->setVisible(!filteredList.isEmpty());
    }
}

void SocialNetworkWindow::onSearchListItemClicked(const QModelIndex &index) {
    QString username = index.data(Qt::DisplayRole).toString();
    // Set the full name in the searchBox
    ui->searchBox->setText(username);

    // Optionally, you might want to hide the searchList after the user has been selected
    ui->searchList->hide();
}
