#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <map>
#include <algorithm>

class Util {
public:
    static std::string getTime(){
		/*
        time_t _tm = time(nullptr);
        struct tm *curTime = localtime(&_tm);
        std::string day = std::to_string(curTime->tm_mday).append("-");
        std::string month = std::to_string(curTime->tm_mon).append("-");
        std::string year = std::to_string(curTime->tm_year + 1900);
        std::string time = month.append(day.append(year));
        std::string hourminsec = std::to_string(curTime->tm_hour).append(
                std::to_string(curTime->tm_min).append(std::to_string(curTime->tm_sec)));
        time.append(hourminsec);
        //return asctime(curTime);
		*/
		return "INVALID_TIME";
    }

    static std::string replaceCharacter(std::string str, char removed, char replace){
        std::replace(str.begin(), str.end(), removed, replace);
        return str;
    }
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

    static void writeFile(const std::string& file_path, const std::string& contents);
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
    std::string getWithDefault(std::string key, std::string defaultValue);

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
    std::map<std::string, std::string> options;
    std::string m_name;

    void readConfig(std::string name);

    void writeConfig();
};

#endif // UTIL_H