#include "user.h"

user:: user (string UID, string user_name, string user_password, string contact, string address, float balance, string status) {
    this->UID = UID;
    this->user_name = user_name;
    this->user_password = user_password;
    this->contact = contact;
    this->address = address;
    this->balance = balance;
    this->status = status;
}