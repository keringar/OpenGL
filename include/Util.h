#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <map>
#include <algorithm>

namespace Util {
    std::string getTime();
    int randomInt(int min = -2147483648, int max = 2147483648);
};

/*
 * Logging class
 */
class Log {
public:
    enum class Channels {
        Error, Warning, None
    };

    static void log(const std::string &data, Channels c = Channels::Error);

private:
    static bool firstRun;
};

/*
 * File read/write class
 */
class File {
public:
    static std::string readString(const std::string &file_path);

    static void writeFile(const std::string &file_path, const std::string &contents);
};

/*
 * Configuration class
 */
class Configuration {
public:
    Configuration(std::string name);

    ~Configuration();

    //Copy constructor
    Configuration(const Configuration &config) : m_name{config.m_name}, options{config.options} {

    }

    //Copy assignment operator
    Configuration &operator=(const Configuration &config) {
        this->m_name = config.m_name;
        this->options = config.options;
        return *this;
    }

    void add(std::string key, std::string value);

    //Returns value
    std::string setValue(std::string key, std::string value);

    std::string get(std::string key);
    std::string get(std::string key, std::string defaultValue);

    int getAsInt(std::string key);

    bool getAsBool(std::string key);

    std::map<std::string, std::string> getOptions() {
        return options;
    }

    std::string getName() {
        return m_name;
    }

    void flush() {
        writeConfig();
    }

private:
    std::string m_name;
    std::map<std::string, std::string> options;

    void readConfig(std::string name);
    void writeConfig();
};

#endif // UTIL_H