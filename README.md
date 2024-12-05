# Dynamic Friend Search Application
<img width="733" alt="image" src="https://github.com/user-attachments/assets/5af4ad3c-cae4-4ec5-9499-fcb4d946cf0e">
<img width="733" alt="image" src="https://github.com/user-attachments/assets/6283ed9c-6d04-49b1-b2c0-424f7c78eed6">

## Overview

This project is a social network application that allows users to connect, share posts, and explore friends' profiles through a graphical user interface (GUI) built using Qt. The application provides features such as user login, friend suggestions, profile viewing, and search functionality. It consists of several classes, including `SocialNetworkWindow`, `Network`, `User`, `Post`, and `IncomingPost`, each contributing to different aspects of the application.

The primary purpose of this application is to simulate a social network environment where users can interact by creating profiles, adding friends, and sharing posts. The application demonstrates key functionalities such as dynamic friend recommendations, efficient searching, and interactive user interfaces, making it a great example of a small-scale social platform.

## Features (DynamicFriendSearch)

### 1. User Login and Profile Management

Users can log in by entering their first and last name. Upon successful login, users can view their profile, friends list, and recent posts. Users can also navigate to other users' profiles and see suggestions for potential new friends.

The login process includes validation to ensure that users enter both their first and last names. If the login attempt fails, an appropriate error message is displayed to prompt the user to try again.

### 2. Friend Connections

Users can add new friends by navigating to other users' profiles and clicking the "Add Friend" button. Friend connections can be managed through the `Network` class, which provides methods to add and remove friendships between users.

The application also suggests potential friends based on the user's existing network of friends. Friend suggestions are calculated using a scoring system that measures the connection strength between friends of friends, helping users to expand their network.

### 3. Search and Auto-Suggest Functionality (DynamicFriendSearch)

The search feature allows users to find friends by typing names into a search box. As users type, suggestions are displayed dynamically using a `QListView`. The following functionalities are provided:

- **Live Search**: Suggestions appear as users type in the search box, making it easy to find friends with similar names.
- **Search Button**: Users can perform a search by clicking the search button, which will display the matching user's profile if found.
- **Search List Click**: Clicking a suggested name will automatically fill the search box, enhancing the ease of finding friends.

The search functionality uses a `QStringListModel` to dynamically filter usernames from the complete list of users in the social network. As users type, the list of matching names is updated in real-time, providing an intuitive and responsive experience.

### 4. Post Management

Users can create and manage posts. The `Post` class represents user posts, while `IncomingPost` represents posts shared between users. Users can view recent posts and filter between public and private posts.

Posts are managed chronologically, allowing users to see the most recent posts first. Users can also filter the posts to view only public ones, enhancing privacy control within the application.

## Code Structure

### 1. `main.cpp`

The entry point for the application. It creates an instance of `QApplication` and `SocialNetworkWindow`, which serves as the main interface of the application.

### 2. `socialnetworkwindow.cpp`

Defines the main window of the application, which handles user interactions such as logging in, viewing profiles, searching for friends, and displaying friend suggestions. This class uses the `Network` class to manage users and their connections.

The `SocialNetworkWindow` class also manages the UI connections, linking user actions (such as clicking buttons or typing in the search box) to corresponding methods. For example, the `updateSearchResults` method is connected to the `textChanged` signal of the search box to provide real-time updates.

### 3. `network.h` and `network.cpp`

These files define the `Network` class, which manages all users and friendships. It provides methods for reading user and post data from files, writing user data, adding/removing friends, suggesting friends, and displaying posts.

The `Network` class also includes functions for computing friend suggestions, using a breadth-first search (BFS) approach to find friends of friends and determine the connection strength based on mutual connections.

### 4. `user.cpp`

Defines the `User` class, which represents individual users in the network. It includes methods for managing user attributes, friends, and posts.

The `User` class allows for adding and removing friends, as well as managing a list of posts. Posts are stored in a vector, and methods are provided to display recent posts or filter them by visibility (public or private).

### 5. `Post.cpp` and `IncomingPost.cpp`

Define the `Post` and `IncomingPost` classes, respectively. The `Post` class represents a user's post, while `IncomingPost` extends `Post` to represent posts shared between users, with an option to specify if the post is public or private.

## Implementation Details

- **Friend Suggestions**: The `Network` class includes a `suggestFriends` method that suggests new friends based on the user's existing connections. This method identifies friends of friends who are not already connected to the user and ranks suggestions based on the number of mutual connections.
- **Shortest Path Calculation**: The application also includes a method to compute the shortest path between two users, showcasing the connection strength between users in the network. This feature can be used to determine how closely connected two users are within the network.
- **File Handling**: Users and posts are read from and written to files (`social_network.txt` and `posts.txt`). The `readUsers` and `readPosts` methods handle the reading process, initializing the social network from stored data. The file format is structured to include user details, friend lists, and post information, ensuring that the social network state is persistent across sessions.

## User Interface

The user interface is built using Qt, with widgets such as `QLineEdit`, `QPushButton`, `QListView`, and `QTableWidget` to provide an interactive experience. The UI includes components for:

- **Login**: Text boxes for entering the user's name. If the user fails to enter both first and last names, an error message is displayed to prompt the correct input.
- **Profile View**: Displays the user's profile information, friends list, and recent posts. Users can also view friend suggestions and add new friends directly from the profile view.
- **Search**: A search box with real-time suggestions to find friends easily. The `QListView` widget displays a filtered list of users that match the search query, making it easy to navigate to the desired profile.

## Running the Application

To run the application, ensure that Qt is installed and that the necessary files (`social_network.txt` and `posts.txt`) are present in the application's working directory. Compile the project and run the resulting executable to start the social network.

## Credits

- **Developer**: Jerry Wang
- **Technologies Used**: C++, Qt Widgets for GUI development.

