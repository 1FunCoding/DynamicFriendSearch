#ifndef USER_H
#define USER_H

//#include "Post.h"
#include "IncomingPost.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>  // Include necessary header for std::getline and std::istringstream

#include "Post.h"

class User {
public:
    // Pre-condition: None
    // Post-condition: 
    //   - Creates a User object with default values:
    //   - id is set to 0.
    //   - name is an empty string.
    //   - year is set to 0.
    //   - zip is set to 0.
    //   - friends list is empty.
    User();
    
    // Pre-condition: 
    //   - The provided 'id' should be a non-negative integer.
    //   - The 'name' argument should not be an empty string.
    //   - 'year' and 'zip' should be non-negative integers.
    // Post-condition: Creates a User object with the specified values:
    //   - id_ is set to the provided 'id'.
    //   - name_ is set to the provided 'name'.
    //   - year_ is set to the provided 'year'.
    //   - zip_ is set to the provided 'zip'.
    //   - friends list is initially empty.
    User(std::size_t id, const std::string& name, std::size_t year, std::size_t zip);

    // Pre-condition: None
    // Post-condition: Returns the user's ID.
    std::size_t getId() const;

    // Pre-condition: None
    // Post-condition: Returns the user's name as a string.
    std::string getName() const;

    // Pre-condition: None
    // Post-condition: Returns the user's birth year.
    std::size_t getYear() const;

    // Pre-condition: None
    // Post-condition: Returns the user's zip code.
    std::size_t getZip() const;

    // Pre-condition: None
    // Post-condition: Returns a reference to the user's list of friends.
    const std::vector<std::size_t>& getFriends() const;

    // Pre-condition: id >= 0
    // Post-condition: Adds the specified user ID to the list of friends if it's not already present.
    void addFriend(std::size_t id);

    // Pre-condition: id >= 0 
    // Post-condition: Removes the specified user ID from the list of friends if it's present.
    void deleteFriend(std::size_t id);

    // Pre-condition: 
    //   - 'post' is a valid non-null pointer to a Post object.
    //   - The Post object pointed by 'post' is not already present in the 'messages_' vector.
    // Post-condition: 
    //   - The Post object pointed by 'post' is added to the 'messages_' vector.
    //   - The 'messages_' vector has the newly added post being the most recent.
    //   - The memory for the Post object remains allocated on the heap.
    void addPost(Post* post);

    // Pre-condition: 
    //   - 'howmany' is a non-negative integer.
    //   - 'messages_' contains valid Post pointers in chronological order.
    //   - Each Post's `displayPost()` starts with "Public" or "Private".
    // Post-condition: 
    //   - Returns a string of up to the most recent 'howmany' posts.
    //   - If 'showOnlyPublic' is true, only public posts are included.
    //   - Posts in the returned string are separated by two newline characters.
    std::string displayPosts(std::size_t howmany, bool showOnlyPublic) const;

    //helper function
    std::size_t getNumPosts() const;
    
private:
    std::size_t id_;
    std::string name_;
    std::size_t year_;
    std::size_t zip_;
    std::vector<std::size_t> friends_;
    // New field for messages
    std::vector<Post*> messages_;

};

#endif // USER_H
