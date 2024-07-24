
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// User class definition
class User {
public:
    string firstName;       // User's first name
    string lastName;        // User's last name
    int age;                // User's age
    string gender;          // User's gender
    string contactNumber;   // User's contact number
    string address;         // User's address
    string email;           // User's email
    string password;        // User's password
    vector<string> hobbies; // List of user's hobbies

    // Default constructor
    User() {}

    // Parameterized constructor
    User(string firstName, string lastName, int age, string gender, string contactNumber,
         string address, string email, string password, vector<string> hobbies)
        : firstName(firstName), lastName(lastName), age(age), gender(gender),
          contactNumber(contactNumber), address(address), email(email),
          password(password), hobbies(hobbies) {}

    // Method to authenticate user based on input password
    bool authenticate(const string& inputPassword) const {
        return password == inputPassword;
    }
};

// Message class definition
class Message {
public:
    string sender;         // Username of the sender
    string receiver;       // Username of the receiver
    string content;        // Message content
    time_t timestamp;      // Time when the message was sent

    // Default constructor
    Message() {}

    // Parameterized constructor
    Message(string sender, string receiver, string content) {
        this->sender = sender;
        this->receiver = receiver;
        this->content = content;
        this->timestamp = time(0); // Set timestamp to current time
    }

    // Method to display message details
    void displayMessage() const {
        cout << "From: " << sender << ", To: " << receiver << ", Message: " << content << ", Timestamp: " << ctime(&timestamp);
    }
};

// SocialGroup class definition
class SocialGroup {
private:
    string groupName;               // Name of the group
    vector<Message> messages;       // List of messages in the group
    set<string> members;            // Set of group members

public:
    // Default constructor
    SocialGroup() {}

    // Parameterized constructor
    SocialGroup(string name) : groupName(name) {}

    // Method to add a member to the group
    void addMember(const string& userName) {
        members.insert(userName);
    }

    // Method to send a message from a sender to all other members in the group
    void sendMessage(const string& sender, const string& content) {
        for (const auto& member : members) {
            if (member != sender) {
                messages.emplace_back(sender, member, content);
            }
        }
    }

    // Method to add a general message to the group
    void addMessage(const string& userName, const string& content) {
        messages.emplace_back(userName, "", content);
    }

    // Method to display all messages in the group
    void displayMessages() const {
        cout << "Messages in Group: " << groupName << "\n";
        for (const auto& msg : messages) {
            msg.displayMessage();
        }
    }

    // Method to display all members of the group
    void displayMembers() const {
        cout << "Group " << groupName << " Members: ";
        for (const auto& member : members) {
            cout << member << " ";
        }
        cout << endl;
    }
};

// Global variables
map<string, User> mapUserName;           // Map of usernames to User objects
map<string, set<string>> friends;        // Map of usernames to their list of friends

// Function to add a new user to the system
void addUser(const string& userName, const User& user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "Username Already Taken\n";
    }
}

// Function to establish a friendship between two users
void makeThemFriends(const string& userName1, const string& userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        friends[userName1].insert(userName2);
        friends[userName2].insert(userName1);
    } else {
        cout << "One or both usernames do not exist\n";
    }
}

// Function to display all users in the system
void displayAllUsers() {
    for (const auto& userPair : mapUserName) {
        const auto& user = userPair.second;
        cout << "Username: " << userPair.first 
             << ", Name: " << user.firstName << " " << user.lastName
             << ", Age: " << user.age
             << ", Gender: " << user.gender
             << ", Contact: " << user.contactNumber
             << ", Address: " << user.address
             << ", Email: " << user.email
             << ", Hobbies: ";
        for (const auto& hobby : user.hobbies) {
            cout << hobby << " ";
        }
        cout << endl;
    }
}

// Function to display all friendships in the system
void displayAllFriendships() {
    for (const auto& friendPair : friends) {
        cout << friendPair.first << ": ";
        for (const auto& friendName : friendPair.second) {
            cout << friendName << " ";
        }
        cout << endl;
    }
}

// Function to display mutual friends between two users
void displayMutualFriends(const string& userName1, const string& userName2) {
    if (mapUserName.find(userName1) == mapUserName.end() || mapUserName.find(userName2) == mapUserName.end()) {
        cout << "One or both usernames do not exist.\n";
        return;
    }

    set<string> friends1 = friends[userName1];
    set<string> friends2 = friends[userName2];

    cout << "Mutual friends between " << userName1 << " and " << userName2 << ":\n";

    for (const auto& friend1 : friends1) {
        if (friends2.find(friend1) != friends2.end()) {
            cout << "- " << friend1 << "\n";
        }
    }
}

// Function to authenticate a user based on username and password
bool authenticateUser(const string& userName, const string& password) {
    auto it = mapUserName.find(userName);
    if (it != mapUserName.end()) {
        return it->second.authenticate(password);
    }
    return false;
}

// Main function
int main() {
    int choice;
    string userName, firstName, lastName, gender, contactNumber, address, email, password, hobby, friendName, groupName, content;
    int age;
    vector<string> hobbies;
    User newUser;
    SocialGroup group("Goa Trip");

    while (true) {
        cout << "1. Add User\n2. Make Friends\n3. Display All Users\n4. Display All Friendships\n5. Display Mutual Friends\n6. Send Message\n7. Add Group Member\n8. Display Group Messages\n9. Authenticate User\n10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Add a new user
            cout << "Enter username: ";
            cin >> userName;
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter gender: ";
            cin >> gender;
            cout << "Enter contact number: ";
            cin >> contactNumber;
            cout << "Enter address: ";
            cin.ignore(); // Ignore newline character from previous input
            getline(cin, address);
            cout << "Enter email: ";
            getline(cin, email);
            cout << "Enter password: ";
            getline(cin, password);
            hobbies.clear();
            cout << "Enter hobbies (type 'end' to stop): ";
            while (true) {
                getline(cin, hobby);
                if (hobby == "end") break;
                hobbies.push_back(hobby);
            }
            newUser = User(firstName, lastName, age, gender, contactNumber, address, email, password, hobbies);
            addUser(userName, newUser);
            break;
        case 2:
            // Make two users friends
            cout << "Enter your username: ";
            cin >> userName;
            cout << "Enter friend's username: ";
            cin >> friendName;
            makeThemFriends(userName, friendName);
            break;
        case 3:
            // Display all users
            displayAllUsers();
            break;
        case 4:
            // Display all friendships
            displayAllFriendships();
            break;
        case 5:
            // Display mutual friends between two users
            cout << "Enter First Username: ";
            cin >> userName;
            cout << "Enter Second Username: ";
            cin >> friendName;
            displayMutualFriends(userName, friendName);
            break;
        case 6:
            // Send a message from one user to another
            cout << "Enter Sender Username: ";
            cin >> userName;
            cout << "Enter Receiver Username: ";
            cin >> friendName;
            cout << "Enter Message Content: ";
            cin.ignore(); // Ignore newline character from previous input
            getline(cin, content);
            {
                Message msg(userName, friendName, content);
                msg.displayMessage();
                group.addMessage(userName, content);
            }
            break;
        case 7:
            // Add a user to the group
            cout << "Enter Username to add to group: ";
            cin >> userName;
            group.addMember(userName);
            break;
        case 8:
            // Display all messages in the group
            group.displayMessages();
            break;
        case 9:
            // Authenticate a user
            cout << "Enter username: ";
            cin >> userName;
            cout << "Enter password: ";
            cin >> password;
            if (authenticateUser(userName, password)) {
                cout << "Authentication successful!" << endl;
            } else {
                cout << "Authentication failed. Check your username or password." << endl;
            }
            break;
        case 10:
            // Exit the program
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}

