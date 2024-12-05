

#include "IncomingPost.h"

IncomingPost::IncomingPost(): isPublic_(false)
// Default constructor
{
}

 

IncomingPost::IncomingPost(std::size_t id, const std::string& message, std::size_t likes, std::string name, bool isPublic):Post(id,message + "from" + name, likes)
{
	
	isPublic_ = isPublic;
}




/*

std::string IncomingPost::displayPost() const {
    if(isPublic_) {
        return "Public: " + Post::displayPost();
    } else {
        return "Private: " + Post::displayPost();
    }
}
*/