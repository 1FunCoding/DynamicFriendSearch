#include "network.h"
#include "user.h"

//Default Constructor
// Pre-condition: None
// Post-condition: 
//   - Initializes a Network object with an empty list of users (users_).
Network::Network() {}

// Desctructor
// Pre-condition: None
// Post-condition: 
//   - Deallocates all dynamically allocated User objects in the users_ vector.
//   - Cleans up any resources used by the Network object.
Network::~Network() {
    // No need to delete the User objects here
}

/*
Network::~Network() {
    // Delete dynamically allocated User objects
    for (User* user : users_) {
        delete user;
    }
}
*/

// Read users from a file
// Precondition: 
//   - filename is not nullptr.
//   - The file specified by fname exists and is accessible for reading.
// Postcondition: 
//   - Users are loaded from the file specified by fname and friends are added to the network.
//   - Returns 0 on success, -1 on failure to open or parse the file.

int Network::readUsers(const char* filename) {
    // Open the file for reading.
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    // Read the first line of the file, which contains the number of users.
    std::size_t numUsers;
    if (!(file >> numUsers)) {
        std::cerr << "Error reading the number of users from the file." << std::endl;
        file.close();
        return -1;
    }

    std::size_t id, zip, year;
    std::string firstName, lastName;
    for (size_t i = 0; i < numUsers; i++) {
        file >> id;
        file >> firstName;
        file >> lastName;
        file >> year;
        file >> zip;

        User* newUser = new User(id, firstName + " " + lastName, year, zip);

        // Consume the trailing newline character after reading zip
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string friendsLine;
        std::getline(file, friendsLine);

        // Use a stringstream to extract friend IDs from the line
        std::istringstream iss(friendsLine);
        std::size_t friendId;
        while (iss >> friendId) {
            newUser->addFriend(friendId);
        }

        users_.push_back(newUser);

    }

    file.close();
    return 0;
}



// Write users to a file
// Precondition: 
//   - filename is not nullptr.
//   - The file specified by fname can be created or overwritten for writing.
// Postcondition: 
//   - Users in the network are written to the file specified by fname.
//   - Returns 0 on success, -1 on failure to open or write to the file.
int Network::writeUsers(const char* fname) {
    std::ofstream file(fname);
    if (!file.is_open()) {
        return -1; // Failed to open the file for writing
    }

    int numUsers = users_.size();
    file << numUsers << '\n';

    for (int i = 0; i < numUsers; ++i) {
        if (users_[i] != nullptr) {
            // Write user ID
            file << i << '\n';

            // Write user information with tabs as delimiters
            file << '\t' << users_[i]->getName() << '\n';
            file << '\t' << users_[i]->getYear() << '\n';
            file << '\t' << users_[i]->getZip() << '\n' << '\t';

            // Write friend connections (IDs separated by spaces)
            const std::vector<std::size_t>& friends = users_[i]->getFriends();
            for (std::size_t j = 0; j < friends.size(); ++j) {
                file << friends[j];
                if (j < friends.size() - 1) {
                    file << ' ';
                }
            }
            file << '\n';
        }
    }

    file.close();
    return 0; // Successfully wrote users to the file
}



// Pre-condition: 
//   - 'user' must be a valid pointer to a User object (not nullptr).
// Post-condition:
//   - Adds the provided 'user' to the Network's list of users_.
void Network::addUser(User* user) {
    users_.push_back(user);
}

// Pre-condition: 
//   - 'name1' and 'name2' must be valid user.
//   - A connection between User 'name1' and 'name2' should not already exist.
//   - 'name1' and 'name2' should not refer to the same user.
// Post-condition:
//   - Establishes a friend connection between the users with names 'name1' and 'name2'.
//   - Returns 0 on success, indicating that the connection has been established.
//   - Returns -1 if either 'name1' or 'name2' is not a valid user name or if the connection could not be established.
int Network::addConnection(const std::string& name1, const std::string& name2) 
{
    std::size_t id1 = getId(name1);
    std::size_t id2 = getId(name2);

    if (id1 == -1 || id2 == -1) {
        return -1; // Return -1 if either of the users is invalid
    }

    if (id1 == id2) {
        std::cerr << "Error: Cannot create a self-connection." << std::endl;
        return -1; // Return -1 if a self-connection is attempted
    }

    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

    user1->addFriend(id2);
    user2->addFriend(id1);

    return 0; // Return 0 on success
}

// Pre-condition: 
//   - 'name1' and 'name2' must be valid user.
//   - A connection between 'name1' and 'name2' should already exist.
//   - 'name1' and 'name2' should not refer to the same user.
// Post-condition:
//   - Removes the friend connection between the users with names 'name1' and 'name2'.
//   - Returns 0 on success, indicating that the connection has been removed.
//   - Returns -1 if either 'name1' or 'name2' is not a valid user name or if the connection could not be removed.、
int Network::removeConnection(const std::string& name1, const std::string& name2) 
{
    std::size_t id1 = getId(name1);
    std::size_t id2 = getId(name2);

    if (id1 == -1 || id2 == -1) 
    {
        std::cerr << "Error: Invalid user names." << std::endl;
        return -1; // Return -1 if either of the users is invalid
    }

    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

    // Check if both users are friends with each other
    bool friendshipExists1 = false;
    bool friendshipExists2 = false;

    const std::vector<std::size_t>& friends1 = user1->getFriends();
    const std::vector<std::size_t>& friends2 = user2->getFriends();

    for (std::size_t friendId : friends1) {
        if (friendId == id2) {
            friendshipExists1 = true;
            break;
        }
    }

    for (std::size_t friendId : friends2) {
        if (friendId == id1) {
            friendshipExists2 = true;
            break;
        }
    }

    if (friendshipExists1 && friendshipExists2) {
        user1->deleteFriend(id2);
        user2->deleteFriend(id1);
        return 0; // Return 0 on success
    } else {
        std::cerr << "Error: Friendship does not exist." << std::endl;
        return 1; // Return 1 if the friendship does not exist
    }
}


// Pre-condition:
//   - 'name' must be a valid user name in the Network.
// Post-condition:
//   - If a user with the provided 'name' exists in the Network, returns the ID (index) of that user.
//   - If no user with the provided 'name' is found in the Network, returns -1.
std::size_t Network::getId(const std::string& name) const 
{
    for (const User* user : users_) {
        if (user->getName() == name) {
            return user->getId();
        }
    }
    return -1; // Return -1 if the user name is not found
}

// Pre-condition: None
// Post-condition:
//   - Returns the total number of users currently registered in the Network.
std::size_t Network::numUsers() const 
{
    return users_.size();
}

// Pre-condition: 
//   - 'id' must be a valid user ID.
// Post-condition:
//   - If 'id' is within a valid range and corresponds to an existing user, returns a pointer to that User.
//   - If 'id' is out of range or if no user with the provided 'id' is found, returns nullptr.
User* Network::getUser(std::size_t id) const {
    for (User* user : users_) {
        if (user->getId() == id) {
            return user;
        }
    }
    return nullptr; // Return nullptr if the user with the specified ID is not found
}

// Computes the shortest path between two users.
// Pre-condition: 
//   - 'from' and 'to' are valid user IDs.
// Post-condition:
//   - Returns a vector containing a shortest path of vertices starting at User "from" and ending at user "to".
std::vector<std::size_t> Network::shortestPath(std::size_t from, std::size_t to) {
    std::vector<std::size_t> path;
    if (from >= users_.size() || to >= users_.size()) {
        return path;  // Return empty path if invalid user IDs are provided.
    }

    std::vector<bool> visited(users_.size(), false);
    std::vector<std::size_t> predecessor(users_.size(), -1);  // To track path
    std::queue<std::size_t> q;

    visited[from] = true;
    q.push(from);

    while (!q.empty()) {
        std::size_t current = q.front();
        q.pop();

        if (current == to) {
            break;  // Found the destination
        }

        User* currentUser = users_[current];
        for (std::size_t friendId : currentUser->getFriends()) {
            if (!visited[friendId]) {
                visited[friendId] = true;
                q.push(friendId);
                predecessor[friendId] = current;
            }
        }
    }

    if (!visited[to]) {
        return path;  // No path found
    }

    // Build the path from destination to source
    for (std::size_t at = to; at != -1; at = predecessor[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());  // Reverse to get path from source to destination

    return path;
}

// Given a user and a distance， find a user whose relational distance from the given user exactly matches the distance given。
//   - 'from' is a valid user ID.
//   - 'distance' is a positive integer.
// Post-condition:  
//   - 'to' is updated with the ID of the user found.
//   - Returns a vector containing a path of vertices starting at User "from" and ending at user "to".
std::vector<std::size_t> Network::distanceUser(std::size_t from, std::size_t& to, std::size_t distance) {
    std::vector<std::size_t> result;
    if (from >= users_.size()) {
        to = -1;
        return result;  // Return empty vector if starting user ID is invalid
    }

    // Data structures for BFS
    std::queue<std::size_t> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<std::size_t> parent(users_.size(), -1);
    std::vector<std::size_t> level(users_.size(), -1);

    // Initialize BFS starting from the 'from' user
    q.push(from);
    visited[from] = true;
    level[from] = 0;

    while (!q.empty()) {
        std::size_t current = q.front();
        q.pop();

        if (level[current] == distance) {
            // Found a user at the desired distance
            to = current;

            // Reconstruct the path
            while (current != from) {
                result.push_back(current);
                current = parent[current];
            }
            result.push_back(from);
            std::reverse(result.begin(), result.end());  // Reverse to get path from source to destination
            return result;
        }

        // Explore friends of the current user
        for (std::size_t friendId : users_[current]->getFriends()) {
            if (!visited[friendId]) {
                visited[friendId] = true;
                parent[friendId] = current;
                level[friendId] = level[current] + 1;
                q.push(friendId);
            }
        }
    }

    // No user found at the desired distance
    to = -1;
    return result;  // Return empty vector
}


// Pre-condition: 
//   - 'who' is a valid user ID in the network.
//   - 'score' is a reference variable that will store the highest friendship score found among the suggestions.
// Post-condition:  
//   - If suggestions are found, the function returns a list of user IDs that are potential friend suggestions for the user with ID 'who'.
//   - These suggested users are not current friends of the user but have a strong connection to the user's friends.
//   - The returned users are at a relational distance of 2 from the specified user (i.e., friends of friends).
//   - 'score' is updated to the highest friendship score found among the suggestions.
//   - If no suggestions are found, 'score' is set to -1 and the function returns an empty vector.
std::vector<std::size_t> Network::suggestFriends(std::size_t who, std::size_t& score) {
    std::unordered_map<std::size_t, std::size_t> freq_map;
    std::vector<std::size_t> suggestions;

    if (who >= users_.size()) {
        score = -1;
        return suggestions;  // Return empty vector if the user ID is invalid
    }

    // Get direct friends of the specified user
    const std::vector<std::size_t>& direct_friends = users_[who]->getFriends();

    // Populate the frequency map with friends of friends
    for (std::size_t friend_id : direct_friends) {
        for (std::size_t foaf_id : users_[friend_id]->getFriends()) {
            // Exclude direct friends and the user themself
            if (foaf_id != who && std::find(direct_friends.begin(), direct_friends.end(), foaf_id) == direct_friends.end()) {
                freq_map[foaf_id]++;
            }
        }
    }

    // Find the maximum score
    score = 0;
    for (const auto& entry : freq_map) {
        if (entry.second > score) {
            score = entry.second;
        }
    }

    // Extract all users with the maximum score
    for (const auto& entry : freq_map) {
        if (entry.second == score) {
            suggestions.push_back(entry.first);
        }
    }

    if (suggestions.empty()) {
        score = -1;
    }

    return suggestions;
}


// Private helper function for DFS traversal
void Network::DFS(std::size_t user_id, std::vector<bool>& visited, std::vector<std::size_t>& current_group) {
    visited[user_id] = true;
    current_group.push_back(user_id);

    // Explore friends of the current user
    for (std::size_t friend_id : users_[user_id]->getFriends()) {
        if (!visited[friend_id]) {
            DFS(friend_id, visited, current_group);
        }
    }
}

// Pre-condition: 
//   - The network may contain any number of users and connections.
// Post-condition:  
//   - The function uses Depth First Search (DFS) to categorize and find each disjoint set.
//   - The function returns a list of disjoint sets of users.
std::vector<std::vector<std::size_t>> Network::groups() {
    std::vector<bool> visited(users_.size(), false);
    std::vector<std::vector<std::size_t>> connected_components;

    for (std::size_t i = 0; i < users_.size(); i++) {
        if (!visited[i]) {
            std::vector<std::size_t> current_group;
            DFS(i, visited, current_group);
            connected_components.push_back(current_group);
        }
    }

    return connected_components;
}

// Pre-condition: 
//   - 'name' is a non-empty string that corresponds to a user in the network.
//   - 'howmany' is a non-negative integer.
// Post-condition: 
//   - The function returns a string representation of the posts of the user with the name 'name'.
//   - If the user has less than 'howmany' posts, all of the user's posts are displayed.
//   - If the user has more than 'howmany' posts, only the latest 'howmany' posts are displayed.
//   - If the user is not found in the network, the function returns an empty string or an appropriate error message.
std::string Network::displayPosts(const std::string& name, std::size_t howMany) const
{
    // Retrieve the User object given the name (assuming you have a method getUserByName)
    //std::cout<<"!!!!!!!!!!!!!!!!!"<<std::endl;



    size_t id = getId(name);
    User* user = getUser(id);
    if (user) {
        return user->displayPosts(howMany, true);
    }
    return "";  // Return empty string if user not found
}

// Pre-condition: 
//   - 'ownerId' is a valid user ID in the network.
//   - 'message' is non-empty.
//   - 'likes' is non-negative.
//   - If 'incoming' is true, 'author' is a valid user ID.
// Post-condition: 
//   - A new post with the next unique 'messageId' is added to 'ownerId'.
//   - The new post contains the provided 'message', 'likes', and 'isPublic'.
//   - If 'incoming' is true, the post represents an incoming post from 'author'.
void Network::addPost(std::size_t ownerId, const std::string& message, std::size_t likes, bool incoming, std::size_t author, bool isPublic) {
    User* user = getUser(ownerId);
    if (user) {
        std::size_t messageId = user->getNumPosts();  // Assuming you have a method to get count of messages
        Post* newPost;
        std::string name = getUser(author)->getName();
        if (incoming) {
            newPost = new IncomingPost(messageId, message, likes, name, isPublic);
        } else {
            newPost = new Post(messageId, message, likes);
        }
        user->addPost(newPost);
    }
}

 // Reads posts from a file and adds them to users in the network.
 //
 // Preconditions:
 // - `filename` points to an existing file with the expected format.
 // 
 // Postconditions:
 // - Posts are added to respective users in the network.
 // - Returns 1 if successful, -1 otherwise.
int Network::readPosts(const char* filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return -1;  // Error in opening the file
    }

    int numPosts;
    infile >> numPosts;
    std::string tempLine;
    std::getline(infile, tempLine);  // Consume the newline after numPosts

     for (int i = 0; i < numPosts; i++) {
        
         std::size_t messageId;
         std::string messageText, visibility, authorName;
         std::size_t ownerId;
         std::size_t numberOfLikes;


         //std::getline(infile,visibility);
     //    messageId = 
         infile >> messageId;

         //std::cout<<"message id: "<<messageId<<std::endl;
         //std::cout<<messageId<<std::endl;
         std::getline(infile, tempLine);  // Consume the newline after messageId
         std::getline(infile, messageText);
         messageText.erase(messageText.begin());
         infile >> ownerId;
         //std::cout<<"ownerid: "<<ownerId<<std::endl;
        infile>>numberOfLikes;
        //std::cout<<"numberOfLikes: "<<numberOfLikes<<std::endl;
        // Fetch the user based on ownerId
        //std::cout<<ownerId<<std::endl;
        User* user = getUser(ownerId);  // Assuming a method exists to fetch user by ID

         // Check for visibility (public/private)
         std::getline(infile, tempLine);  // Consume the newline after numberOfLikes
         std::getline(infile, visibility);
         //std::cout<<visibility<<std::endl;

         visibility.erase(0,1);

         if(visibility.empty()){
            user->addPost(new Post(messageId, messageText, numberOfLikes));
            continue;
           
        }   

        std::getline(infile, authorName);

        authorName.erase(authorName.begin());
       // std::cout<<"authorName: "<<authorName<<std::endl;

         if (visibility == "public") {


            bool isPublic = true;
             // Create IncomingPost object and add to user
             // Post* nPost = new IncomingPost(messageId, messageText, numberOfLikes, authorName, isPublic);
             user->addPost(new IncomingPost(messageId, messageText, numberOfLikes, authorName, isPublic));  // Assuming addPost method exists in User class
         } else {
            //std::cout<<"here"<<std::endl;
             //Post* nPost= new Post(messageId, messageText, numberOfLikes);
            user->addPost(new Post(messageId, messageText, numberOfLikes));  
         }
        // std::cout<<"i: "<<i<<std::endl;
     }

    infile.close();
    return 0;  // Successfully read posts
}


std::vector<std::string> Network::getAllUserNames() const {
    std::vector<std::string> userNames;
    for (const User* user : users_) {
         userNames.push_back(user->getName());
    }
    return userNames;
}
