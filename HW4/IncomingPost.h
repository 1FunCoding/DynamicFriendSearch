#ifndef INCOMINGPOST_H
#define INCOMINGPOST_H
#include "Post.h"


class IncomingPost : public Post {
public:
    // Constructors
    IncomingPost();  // Default constructor
    IncomingPost(std::size_t id, const std::string& message, std::size_t likes, std::string name, bool isPublic);  // Parameterized constructor

    // Overridden displayPost method
    virtual std::string displayPost() const override
   {
        if(isPublic_)
        {
            return "Public: " + Post::displayPost();
        }
        else
        {
            return "Private: " + Post::displayPost();

        }
    } 

private:
    bool isPublic_;
};


#endif