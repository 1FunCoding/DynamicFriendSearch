#ifndef POST_H
#define POST_H

#include <string>

class Post {
public:
    
    // Pre-condition:
    //   - None
    // Post-condition:
    //   - A default Post object is created with uninitialized or default values.
    Post();  // Default constructor

    // Pre-condition:
    //   - 'message' is a non-empty string.
    //   - 'id' and 'likes' are non-negative integers.
    // Post-condition:
    //   - A Post object is created with the provided id, message, and likes values.
    Post(std::size_t id, const std::string& message, std::size_t likes);  // Primary constructor

    // Pre-condition:
    //   - The Post object is initialized.
    // Post-condition:
    //   - Returns a string representation of the post's message followed by its likes count.
    virtual std::string displayPost() const {
    return message_ + "\nLiked by " + std::to_string(likes_) + " people";
    }

    // Accessor methods
    std::size_t getId() const;
    std::string getMessage() const;
    std::size_t getLikes() const;

private:
    std::size_t id_;
    std::string message_;
    std::size_t likes_;
};

#endif // POST_H
