#ifndef NETWORK_H
#define NETWORK_H

#include "user.h" // Include the User class header
//#include "Post.h"
#include "IncomingPost.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>

class Network {
public:
    //Default Constructor
    // Pre-condition: None
    // Post-condition: 
    //   - Initializes a Network object with an empty list of users (users_).
    Network();

    // Desctructor
    // Pre-condition: None
    // Post-condition: 
    //   - Deallocates all dynamically allocated User objects in the users_ vector.
    //   - Cleans up any resources used by the Network object.
    ~Network();

    // Read users from a file
    // Precondition: 
    //   - filename is not nullptr.
    //   - The file specified by fname exists and is accessible for reading.
    // Postcondition: 
    //   - Users are loaded from the file specified by fname and friends are added to the network.
    //   - Returns 0 on success, -1 on failure to open or parse the file.
    int readUsers(const char* filename);

    // Write users to a file
    // Precondition: 
    //   - filename is not nullptr.
    //   - The file specified by fname can be created or overwritten for writing.
    // Postcondition: 
    //   - Users in the network are written to the file specified by fname.
    //   - Returns 0 on success, -1 on failure to open or write to the file.
    int writeUsers(const char* filename);

    // Pre-condition: 
    //   - 'user' must be a valid pointer to a User object (not nullptr).
    // Post-condition:
    //   - Adds the provided 'user' to the Network's list of users_.
    void addUser(User* user);

    // Pre-condition: 
    //   - 'name1' and 'name2' must be valid user.
    //   - A connection between User 'name1' and 'name2' should not already exist.
    //   - 'name1' and 'name2' should not refer to the same user.
    // Post-condition:
    //   - Establishes a friend connection between the users with names 'name1' and 'name2'.
    //   - Returns 0 on success, indicating that the connection has been established.
    //   - Returns -1 if either 'name1' or 'name2' is not a valid user name or if the connection could not be established.
    int addConnection(const std::string& name1, const std::string& name2);

    // Pre-condition: 
    //   - 'name1' and 'name2' must be valid user.
    //   - A connection between 'name1' and 'name2' should already exist.
    //   - 'name1' and 'name2' should not refer to the same user.
    // Post-condition:
    //   - Removes the friend connection between the users with names 'name1' and 'name2'.
    //   - Returns 0 on success, indicating that the connection has been removed.
    //   - Returns -1 if either 'name1' or 'name2' is not a valid user name or if the connection could not be removed.
    int removeConnection(const std::string& name1, const std::string& name2);

    // Pre-condition:
    //   - 'name' must be a valid user name in the Network.
    // Post-condition:
    //   - If a user with the provided 'name' exists in the Network, returns the ID (index) of that user.
    //   - If no user with the provided 'name' is found in the Network, returns -1.
    std::size_t getId(const std::string& name) const;

    // Pre-condition: None
    // Post-condition:
    //   - Returns the total number of users currently registered in the Network.
    std::size_t numUsers() const;

    // Pre-condition: 
    //   - 'id' must be a valid user ID.
    // Post-condition:
    //   - If 'id' is within a valid range and corresponds to an existing user, returns a pointer to that User.
    //   - If 'id' is out of range or if no user with the provided 'id' is found, returns nullptr.
    User* getUser(std::size_t id) const;

    // Computes the shortest path between two users.
    // Pre-condition: 
    //   - 'from' and 'to' are valid user IDs.
    // Post-condition:
    //   - Returns a vector containing a shortest path of vertices starting at User "from" and ending at user "to".
    std::vector<std::size_t> shortestPath(std::size_t from, std::size_t to);

    // Pre-condition: 
    //   - 'from' is a valid user ID.
    //   - 'distance' is a positive integer.
    // Post-condition:  
    //   - 'to' is updated with the ID of the user found.
    //   - Returns a vector containing a path of vertices starting at User "from" and ending at user "to".
    std::vector<std::size_t> distanceUser(std::size_t from, std::size_t& to, std::size_t distance);


    // Pre-condition: 
    //   - 'who' is a valid user ID in the network.
    //   - 'score' is a reference variable that will store the highest friendship score found among the suggestions.
    // Post-condition:  
    //   - If suggestions are found, the function returns a list of user IDs that are potential friend suggestions for the user with ID 'who'.
    //   - These suggested users are not current friends of the user but have a strong connection to the user's friends.
    //   - The returned users are at a relational distance of 2 from the specified user (i.e., friends of friends).
    //   - 'score' is updated to the highest friendship score found among the suggestions.
    //   - If no suggestions are found, 'score' is set to -1 and the function returns an empty vector.
    std::vector<std::size_t> suggestFriends(std::size_t who, std::size_t& score);

    // Pre-condition: 
    //   - The network may contain any number of users and connections.
    // Post-condition:  
    //   - The function uses Depth First Search (DFS) to categorize and find each disjoint set.
    //   - The function returns a list of disjoint sets of users.
    std::vector<std::vector<std::size_t>> groups();

    // Pre-condition: 
    //   - 'name' is a non-empty string that corresponds to a user in the network.
    //   - 'howmany' is a non-negative integer.
    // Post-condition: 
    //   - The function returns a string representation of the posts of the user with the name 'name'.
    //   - If the user has less than 'howmany' posts, all of the user's posts are displayed.
    //   - If the user has more than 'howmany' posts, only the latest 'howmany' posts are displayed.
    //   - If the user is not found in the network, the function returns an empty string or an appropriate error message.
    std::string displayPosts(const std::string& name, std::size_t howmany) const;


    // Pre-condition: 
    //   - 'ownerId' is a valid user ID in the network.
    //   - 'message' is non-empty.
    //   - 'likes' is non-negative.
    //   - If 'incoming' is true, 'author' is a valid user ID.
    // Post-condition: 
    //   - A new post with the next unique 'messageId' is added to 'ownerId'.
    //   - The new post contains the provided 'message', 'likes', and 'isPublic'.
    //   - If 'incoming' is true, the post represents an incoming post from 'author'.
    void addPost(std::size_t ownerId, const std::string& message, std::size_t likes, bool incoming, std::size_t author, bool isPublic);

    // Reads posts from a file and adds them to users in the network.
    //
    // Preconditions:
    // - `filename` points to an existing file with the expected format.
    // 
    // Postconditions:
    // - Posts are added to respective users in the network.
    // - Returns 1 if successful, -1 otherwise.
    int readPosts(const char* filename);

    std::vector<std::string> getAllUserNames() const;


private:
    std::vector<User*> users_;
    void DFS(std::size_t user_id, std::vector<bool>& visited, std::vector<std::size_t>& current_group);
};

#endif // NETWORK_H
