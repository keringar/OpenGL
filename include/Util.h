#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <map>

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
    static std::string readFile(std::string file_path);

    static std::string writeFile(std::string file_path);
};

/*
 * Configuration class
 */
class Configuration {
public:
    Configuration(std::string name);
    ~Configuration();

    //Copy constructor
    Configuration(const Configuration& config){
        this->m_name = config.m_name;
        this->options = config.options;
    }

    //Copy assignment operator
    Configuration& operator=(const Configuration& config) {
        this->m_name = config.m_name;
        this->options = config.options;
        return *this;
    }

    void add(std::string key, std::string value);

    //Returns value
    std::string setValue(std::string key, std::string value);

    std::string get(std::string key);

    int getAsInt(std::string key);

    bool getAsBool(std::string key);

    std::map<std::string, std::string> getOptions() {
        return options;
    }

    std::string getName() {
        return m_name;
    }

private:
    std::map<std::string, std::string> options;
    std::string m_name;

    void readConfig(std::string name);

    void writeConfig();
};

#endif // UTIL_H