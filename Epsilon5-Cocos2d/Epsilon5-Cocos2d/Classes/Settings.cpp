#include "Settings.h"

#include "Exception.h"

#define checkKey(expression, ...) check(expression, KeyNotFountException, ##__VA_ARGS__)

Settings::Settings() {
    mValues.insert(std::make_pair("Host", "193.169.33.254"));
    mValues.insert(std::make_pair("Port", "14567"));
    mValues.insert(std::make_pair("UserName", "Marvel"));
    mValues.insert(std::make_pair("Password", "test"));
}

Settings::~Settings() {
}

const std::string& Settings::getString(const std::string& key) const {
    auto iterator = mValues.find(key);
    checkKey(iterator != mValues.cend());
    return iterator->second;
}

StringConverter Settings::get(const std::string& key) const {
    return fromString(getString(key));
}
