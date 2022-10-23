#include "UserManager.h"


User UserManager::giveNewUserData() {
    User user;
    user.setUserId(getNewUserId());

    string login;
    do {
        cout << "Give login: ";
        cin >> login;
        user.setLogin(login);
    } while (isLoginExist(user.getLogin()) == true);

    string password;
    cout << "Give password: ";
    cin >> password;
    user.setPassword(password);

    string name;
    cout << "Give name: ";
    cin >> name;
    user.setName(name);

    string surname;
    cout << "Give surname: ";
    cin >> surname;
    user.setSurname(surname);

    return user;
}

int UserManager::getNewUserId() {
    if (users.empty() == true)
        return 1;
    else
        return users.back().getUserId() + 1;
}

bool UserManager::isLoginExist(string login) {
    for (int i=0; i < users.size(); i++) {
        if (users[i].getLogin() == login) {
            cout << endl << "There is a user with the given login." << endl;
            return true;
        }
    }
    return false;
}

 int UserManager::getLoggedUserId(){
    return idLoggedUser;
 }

 void UserManager::setLoggedUserId(int newId){
    if(newId >= 0)
        idLoggedUser = newId;
 }

 bool UserManager::isUserLoggedIn(){
    if (idLoggedUser > 0)
        return true;
    else
        return false;
 }

 void UserManager::registerUser(){
    User user = giveNewUserData();

    users.push_back(user);
    usersFile.addUserToFile(user);

    cout << endl << "The account has been set up successfully" << endl << endl;
    system("pause");
 }

void UserManager::loggingUser() {
    User user;
    string login = "", password = "";
    login = AuxiliaryMethods::readLine();

    cout << endl << "Give login: ";
    login = AuxiliaryMethods::readLine();

    vector <User>::iterator itr = users.begin();

    while (itr != users.end()) {
        if (itr -> getLogin() == login) {
            for (int numberOfAttempts = 3; numberOfAttempts > 0; numberOfAttempts--) {
                cout << "Give password. Attempts left: " << numberOfAttempts << ": ";

                password = AuxiliaryMethods::readLine();

                if (itr -> getPassword() == password) {
                    idLoggedUser = itr -> getUserId();
                    cout << endl << "You are logged in." << endl << endl;
                    system("pause");
                    return;
                }
            }
            cout << "Incorrect password entered 3 times." << endl;
            system("pause");
            return;
        }
        itr++;
    }
    cout << "There is no user with this login." << endl << endl;
    system("pause");
    return;
}

void UserManager::logoutUser(){
    idLoggedUser = 0;
}

void UserManager::changePasswordOfLoggedUser(int idLoggedUser){
    string newPassword = "";
    cout << "Give new password: ";
    cin >> newPassword;

    for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        if (itr -> getUserId() == idLoggedUser)
        {
            itr -> setPassword(newPassword);
            cout << "Password has been changed." << endl << endl;
            system("pause");
        }
    }
    usersFile.changePasswordInXML(idLoggedUser, newPassword);

}
