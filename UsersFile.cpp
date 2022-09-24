#include "UsersFile.h"

string UsersFile::getUsersFileName(){
    return USERS_FILE_NAME;
}

void UsersFile::addUserToFile(User user){

    bool fileExist = xmlUsers.Load("users.xml");

    if (!fileExist)
    {
        xmlUsers.AddElem("Users");
    }

    xmlUsers.FindElem();
    xmlUsers.IntoElem();
    xmlUsers.AddElem("User");
    xmlUsers.IntoElem();
    xmlUsers.AddElem("UserId", user.getUserId());
    xmlUsers.AddElem("Login", user.getLogin());
    xmlUsers.AddElem("Password", user.getPassword());
    xmlUsers.AddElem("Name", user.getName());
    xmlUsers.AddElem("Surname", user.getSurname());

    xmlUsers.Save("users.xml");


}

vector <User> UsersFile::loadUsersFromFile(){

    User user;
    vector <User> users;
    xmlUsers.Load("users.xml");
    xmlUsers.ResetPos();

    while(xmlUsers.FindElem()){
        xmlUsers.FindElem();
        xmlUsers.IntoElem();
        xmlUsers.FindElem();
        xmlUsers.IntoElem();
        xmlUsers.FindElem();
        user.setUserId(AuxiliaryMethods::convertStringToInt(xmlUsers.GetData()));
        xmlUsers.FindElem();
        user.setLogin(xmlUsers.GetData());
        xmlUsers.FindElem();
        user.setPassword(xmlUsers.GetData());
        xmlUsers.FindElem();
        user.setName(xmlUsers.GetData());
        xmlUsers.FindElem();
        user.setSurname(xmlUsers.GetData());
        users.push_back(user);

    }


}
