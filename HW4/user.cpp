#include "user.h"

#include <vector>
// Pre-condition: None
// Post-condition: 
//   - Creates a User object with default values:
//   - id is set to 0.
//   - name is an empty string.
//   - year is set to 0.
//   - zip is set to 0.
//   - friends list is empty.
User::User() : id_(0), name_(""), year_(0), zip_(0) {
    messages_= std::vector<Post*>();
}

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
User::User(std::size_t id, const std::string& name, std::size_t year, std::size_t zip)
    : id_(id), name_(name), year_(year), zip_(zip) {
        messages_= std::vector<Post*>();
    }

// Pre-condition: None
// Post-condition: Returns the user's ID.
std::size_t User::getId() const {
    return id_;
}

// Pre-condition: None
// Post-condition: Returns the user's name as a string.
std::string User::getName() const {
    return name_;
}

// Pre-condition: None
// Post-condition: Returns the user's birth year.
std::size_t User::getYear() const {
    return year_;
}

// Pre-condition: None
// Post-condition: Returns the user's zip code.
std::size_t User::getZip() const{
    return zip_;
}

// Pre-condition: None
// Post-condition: Returns a reference to the user's list of friends.
 const std::vector<std::size_t>& User::getFriends() const{
    return friends_;
}

// Pre-condition: id >= 0
// Post-condition: Adds the specified user ID to the list of friends if it's not already present.
void User::addFriend(std::size_t id) {
    // Check if id is already in the list of friends
    for (std::size_t friendId : friends_) {
        if (friendId == id) {
            // Friend is already in the list, so do nothing
            return;
        }
    }
    // Friend is not in the list,  add them
    friends_.push_back(id);
}

// Pre-condition: id >= 0
// Post-condition: Removes the specified user ID from the list of friends if it's present.
void User::deleteFriend(std::size_t id) {
    // Find the friend in the list and remove them
    for (std::vector<std::size_t>::iterator it = friends_.begin(); it != friends_.end(); ++it) {
        if (*it == id) {
            friends_.erase(it);
            return;
        }
    }
}

// Pre-condition: 
//   - 'post' is a valid non-null pointer to a Post object.
//   - The Post object pointed by 'post' is not already present in the 'messages_' vector.
// Post-condition: 
//   - The Post object pointed by 'post' is added to the 'messages_' vector.
//   - The 'messages_' vector has the newly added post being the most recent.
//   - The memory for the Post object remains allocated on the heap.
void User::addPost(Post* Input){
    //std::cout<<"here3"<<std::endl;
    messages_.push_back(Input);
   //std::cout<<messages_.size()<<std::endl;
}

// Pre-condition: 
//   - 'howmany' is a non-negative integer.
//   - 'messages_' contains valid Post pointers in chronological order.
//   - Each Post's `displayPost()` starts with "Public" or "Private".
// Post-condition: 
//   - Returns a string of up to the most recent 'howmany' posts.
//   - If 'showOnlyPublic' is true, only public posts are included.
//   - Posts in the returned string are separated by two newline characters.
std::string User::displayPosts(std::size_t howmany, bool showOnlyPublic) const
{
    std::string output;
    std::size_t count = 0;

    // Loop through the messages in reverse (from most recent)
    int indx=messages_.size()-1;
//    std::cout<<indx<<std::endl;
    while(indx>=0 && count<howmany) {
        //std::cout<<indx<<std::endl;
        std::string postDisplay = messages_[indx--]->displayPost();
        //std::cout<<postDisplay<<std::endl;
        // If we are to show only public and this post is private, skip
        if (showOnlyPublic && postDisplay.substr(0, 7) == "Private") 
        {
            continue;
        }

        // Add the post's display to the output and increment the count
        output += postDisplay + "\n\n";
        count++;
    }

    return output;
}

//helper function
std::size_t User::getNumPosts() const{
    return messages_.size();
}

