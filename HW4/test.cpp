#include <iostream>
#include <cassert>
#include "network.h"
#include "user.h"
#include "IncomingPost.h"
#include "Post.h"

void testConstructorGetter();
void testAddFriend();
void testDeleteFriend();
void testAddRemoveConnection();
void testGetUsers();
void testDistanceUser();
void testShortestPath();
void testSuggestFriends();
void testGroups();
void testAddPost();
void testDisplayPosts();


void testConstructorGetter() {
    std::cout << "test Constructor Getter... ";
    User u(3, "Jason Chen", 2000, 94087);
    assert(u.getId() == 3);
    assert(u.getName() == "Jason Chen");
    assert(u.getYear() == 2000);
    assert(u.getZip() == 94087);
    std::cout << "Passed!" << std::endl;
}

void testAddFriend() {
    std::cout << "test Add Friend... ";
    User u1(1, "Alice", 1995, 90210);
    User u2(2, "Bob", 1990, 90211);

    u1.addFriend(2);
    u2.addFriend(1);

    const std::vector<std::size_t>& friends1 = u1.getFriends();
    const std::vector<std::size_t>& friends2 = u2.getFriends();

    assert(friends1.size() == 1);
    assert(friends1[0] == 2);
    assert(friends2.size() == 1);
    assert(friends2[0] == 1);

    // Adding the same friend again should have no effect
    u1.addFriend(2);
    assert(friends1.size() == 1);
    std::cout << "Passed!" << std::endl;
}

void testDeleteFriend() {
    std::cout << "test Delete Friend... ";
    User u1(1, "Alice", 1995, 90210);
    User u2(2, "Bob", 1990, 90211);

    u1.addFriend(2);
    u2.addFriend(1);

    u1.deleteFriend(2);
    u2.deleteFriend(1);

    const std::vector<std::size_t>& friends1 = u1.getFriends();
    const std::vector<std::size_t>& friends2 = u2.getFriends();

    assert(friends1.empty());
    assert(friends2.empty());

    // Deleting a friend that doesn't exist should have no effect
    u1.deleteFriend(2);
    assert(friends1.empty());
    std::cout << "Passed!" << std::endl;
}




void testAddRemoveConnection() {
    std::cout << "test Add and Remove Connection... ";
    Network network;

    User* u1= new User(1, "Alice", 1995, 90210);
    User* u2= new User(2, "Bob", 1990, 90211);
    User* u3= new User(3, "Charlie", 1985, 90212);

    network.addUser(u1);
    network.addUser(u2);
    network.addUser(u3);

    // Add connections
    assert(network.addConnection("Alice", "Bob") == 0);
    assert(network.addConnection("Bob", "Charlie") == 0);

    // Check if connections were added correctly
    assert(u1->getFriends().size() == 1);
    assert(u2->getFriends().size() == 2);

    // Remove connections
    assert(network.removeConnection("Alice", "Bob") == 0);
    assert(network.removeConnection("Bob", "Charlie") == 0);

    // Check if connections were removed correctly
    assert(u1->getFriends().empty());
    assert(u2->getFriends().empty());


    std::cout << "Passed!" << std::endl;
}



// Function to test getting users by ID and name
void testGetUsers() {
    std::cout << "test Get Users by ID and name...";
    Network network;

    // Create and add some User objects to the network
    User* u1 = new User(1, "Alice", 1995, 90210);
    User* u2 = new User(2, "Bob", 1990, 90211);
    network.addUser(u1);
    network.addUser(u2);

    // Get users by ID
    User* retrievedU1 = network.getUser(1);
    User* retrievedU2 = network.getUser(2);

    // Check if retrieved users by ID match the original ones
    assert(retrievedU1 == u1);
    assert(retrievedU2 == u2);

    // Get users by name
    std::string name1 = "Alice";
    std::string name2 = "Bob";
    User* retrievedByName1 = network.getUser(network.getId(name1));
    User* retrievedByName2 = network.getUser(network.getId(name2));

    // Check if retrieved users by name match the original ones
    assert(retrievedByName1 == u1);
    assert(retrievedByName2 == u2);

    std::cout << "Passed!" << std::endl;
    assert(network.numUsers()==2);
    std::cout << "Test numUsers...Passed!"<<std::endl;
}



void testDistanceUser() {
    std::cout << "test distanceUser... ";
    Network net;
    // Populate the network with users and connections
    User u1(0, "Dave", 2002, 12348);
    User u2(1, "Eva", 2003, 12349);
    User u3(2, "Frank", 2004, 12350);
    net.addUser(&u1);
    net.addUser(&u2);
    net.addUser(&u3);
    net.addConnection("Dave", "Eva");
    
    // Test the distanceUser function
    std::size_t target_id = -1;
    std::vector<std::size_t> path = net.distanceUser(0, target_id, 2);
    assert(path.size() == 0); // There's no user 2 hops away from Dave
    
    std::cout << "Passed!" << std::endl;
}

void testShortestPath() {
    std::cout << "test shortestPath... ";
    Network network;
    // Populate the network with users and connections
    User u1(0, "Dave", 2002, 12348);
    User u2(1, "Eva", 2003, 12349);
    User u3(2, "Frank", 2004, 12350);
    network.addUser(&u1);
    network.addUser(&u2);
    network.addUser(&u3);
    network.addConnection("Dave", "Eva");
    network.addConnection("Eva","Frank");

    std::vector<std::size_t> path = network.shortestPath(0,2);
    /*
    for (int i=0; i<path.size(); i++) {
        std::cout << path[i] << "-> " <<std::endl;
    }    
    */
    assert(path.size() == 3);


    std::cout << "Passed!" << std::endl;
}

void testSuggestFriends() {
    std::cout << "test suggestFriends... ";
    Network network;
    std::size_t score;

    // Create and add users to the network
    User u1(0, "A", 2000, 10000);
    User u2(1, "B", 2001, 10001);
    User u3(2, "C", 2002, 10002);
    User u4(3, "D", 2003, 10003);

    network.addUser(&u1);
    network.addUser(&u2);
    network.addUser(&u3);
    network.addUser(&u4);

    // Add connections
    network.addConnection("A", "B");
    network.addConnection("B", "C");
    network.addConnection("C", "D");

    std::vector<std::size_t> suggested = network.suggestFriends(0, score);
    assert(suggested.size() == 1);
    assert(suggested[0] == 2);
    assert(score >= 0);  // Assuming score is non-negative

    std::cout << "Passed!" << std::endl;
}


void testGroups() {
    std::cout << "test groups... ";
    Network network;

    // Create and add users to the network
    User u1(0, "A", 2000, 10000);
    User u2(1, "B", 2001, 10001);
    User u3(2, "C", 2002, 10002);
    User u4(3, "D", 2003, 10003);

    network.addUser(&u1);
    network.addUser(&u2);
    network.addUser(&u3);
    network.addUser(&u4);

    // Add connections
    network.addConnection("A", "B");

    std::vector<std::vector<std::size_t>> groupings = network.groups();
    assert(groupings.size() == 3);

    std::cout << "Passed!" << std::endl;
}


    
void testAddPost() {
    
    std::cout << "test Add Post... ";
    Network network;
    User user(0, "Test User", 2000, 12345);
    network.addUser(&user);
    
    // Add a post
    network.addPost(0, "Hello, this is a test post!", 10, false, 0, true);

    User* retrievedUser = network.getUser(0);
    assert(retrievedUser->getNumPosts() == 1); // Check if the post count has increased
    std::cout << "Passed!" << std::endl;
}

void testDisplayPosts() {
    
    std::cout << "test Display Posts... ";
    Network network;
    User user(0, "Test User", 2000, 12345);
    network.addUser(&user);
    
    // Add a post
    network.addPost(0, "Hello, this is a test post!", 10, false, 0, true);
    std::string displayedPosts = network.displayPosts("Test User", 1);
    
    assert(displayedPosts.find("Hello, this is a test post!") != std::string::npos); // Check if the post message is in the displayed posts
    std::cout << "Passed!" << std::endl;
    
}

void testUserAddPost(){
    User* u1= new User(0, "Test User", 2000, 12345);
    Post* p1 = new Post(3,"string",5);
    u1->addPost(p1);



}



int main() {
    
    //test functionalities of user.cpp 

    testConstructorGetter();
    testAddFriend();
    testDeleteFriend();
    //test the functionality of network.cpp
    testAddRemoveConnection();
    testGetUsers();
    testDistanceUser();
    testShortestPath();
    testSuggestFriends();
    testGroups();
    testAddPost();
    testDisplayPosts();



    //test destructor
    Network network;
    network.~Network();

    testAddPost();

    std::cout << "All tests passed!" << std::endl;
    std::cout<< std::endl;
    return 0;
}



//The functions looks good and I did not find problem involving it. 



