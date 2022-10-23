#include "UsersFile.h"

string UsersFile::getFileName(){
    return USERS_FILE_NAME;
}

void UsersFile::addUserToFile(User user){

    bool fileExist = xmlUsers.Load(USERS_FILE_NAME);

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

    xmlUsers.Save(USERS_FILE_NAME);


}

vector <User> UsersFile::loadUsersFromFile(){

    User user;
    vector <User> users;

    if (xmlUsers.Load(USERS_FILE_NAME)) {
            xmlUsers.FindElem();
            xmlUsers.IntoElem();

            while(xmlUsers.FindElem("User")){
                xmlUsers.IntoElem();
                xmlUsers.FindElem("UserId");
                user.setUserId(AuxiliaryMethods::convertStringToInt(xmlUsers.GetData()));
                xmlUsers.FindElem("Login");
                user.setLogin(xmlUsers.GetData());
                xmlUsers.FindElem("Password");
                user.setPassword(xmlUsers.GetData());
                xmlUsers.FindElem("Name");
                user.setName(xmlUsers.GetData());
                xmlUsers.FindElem("Surname");
                user.setSurname(xmlUsers.GetData());
                xmlUsers.OutOfElem();

                users.push_back(user);

            }
    }

    return users;

}

 void UsersFile::changePasswordInXML(int userId, string newPassword){
    if (xmlUsers.Load(USERS_FILE_NAME)) {
        xmlUsers.FindElem();
        xmlUsers.IntoElem();

        while (xmlUsers.FindElem("User")) {
            xmlUsers.IntoElem();
            xmlUsers.FindElem("UserId");

            if (xmlUsers.GetData() == AuxiliaryMethods::convertIntToString(userId)) {
                xmlUsers.FindElem("Password");
                xmlUsers.SetData(newPassword);
                xmlUsers.Save(USERS_FILE_NAME);
                break;
            }

            xmlUsers.OutOfElem();
        }
    }
}
