#include "Post.h"

// Pre-condition:
//   - None
// Post-condition:
//   - A default Post object is created with uninitialized or default values.
Post::Post(){

} // Default constructor

// Pre-condition:
//   - 'message' is a non-empty string.
//   - 'id' and 'likes' are non-negative integers.
// Post-condition:
//   - A Post object is created with the provided id, message, and likes values.
Post::Post(std::size_t id, const std::string& message, std::size_t likes)
    : id_(id), message_(message), likes_(likes) {}


/*

virtual std::string Post::displayPost() const {
    return message_ + "\nLiked by " + std::to_string(likes_) + " people";
}
*/

std::size_t Post::getId() const 
{ 
    return id_;
}

std::string Post::getMessage() const{
    return message_;
}

std::size_t Post::getLikes() const{
    return likes_;
}


