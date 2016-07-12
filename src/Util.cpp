#include "Util.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*///////////////
//LOGGING CLASS//
///////////////*/
bool Log::firstRun = true;

//Channels has a default parameter of none
void Log::log(const std::string &data, Channels c) {
    if (!data.empty()) {
        if (firstRun) {
            firstRun = false;
            std::remove("output.log");

            time_t _tm = time(nullptr);
            struct tm *curTime = localtime(&_tm);
            std::string day = std::to_string(curTime->tm_mday).append("-");
            std::string month = std::to_string(curTime->tm_mon).append("-");
            std::string year = std::to_string(curTime->tm_year + 1900);
            std::string time = month.append(day.append(year));
            std::string hourminsec = std::to_string(curTime->tm_hour).append(
                    std::to_string(curTime->tm_min).append(std::to_string(curTime->tm_sec)));
            time.append(hourminsec);

            Log::log(asctime(curTime), Log::Channels::None);
        }

        std::filebuf fb;
        fb.open("output.log", std::ios::out | std::ios::app);
        std::ostream os(&fb);

        std::string modifier;
        switch (c) {
            case Channels::Error:
                modifier = "[Error]";
                break;
            case Channels::Warning:
                modifier = "[Warning]";
                break;
            default:
                modifier = "";
        }

        os << modifier << data << "\n";
        std::cout << modifier << data << "\n";

        fb.close();
    }
}

/*/////////////////////
//CONFIGURATION CLASS//
/////////////////////*/
Configuration::Configuration(std::string name) : m_name(name) {
    readConfig(name);
}

Configuration::~Configuration() {
    writeConfig();
}

//Populates options map with all key-value pairs delineated by '='
void Configuration::readConfig(std::string name) {
    std::fstream file;
    file.open(name.append(".cfg"), std::ios::in);

    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            std::istringstream is_line(line);
            std::string key;
            if (line.at(0) == '#') {
                //Do nothing because comment
            } else {
                if (std::getline(is_line, key, '=')) {
                    std::string value;
                    if (std::getline(is_line, value)) {
                        options.emplace(key, value);
                    }
                }
            }
        }
    }
}

void Configuration::add(std::string key, std::string value) {
    auto it = options.find(key);

    if (it == options.end()) { //Does not exist
        options.emplace(key, value);
    } else {
        options[key] = value;
    }
}

//Returns empty string if not found
std::string Configuration::get(std::string key) {
    return options[key];
}

//Returns value
std::string Configuration::setValue(std::string key, std::string value) {
    options[key] = value;
    return value;
}

//Takes a key, returns value as int
//@return -1 on failure
int Configuration::getAsInt(std::string key) {
    try {
        return std::stoi(options[key]);
    } catch (std::invalid_argument) {
        setValue(key, "-1");
        return -1;
    } catch (std::out_of_range) {
        setValue(key, "-1");
        return -1;
    }
}

bool Configuration::getAsBool(std::string key) {
    if (options[key].compare("true") == 0) {
        setValue(key, "true");
        return true;
    }

    setValue(key, "false");
    return false;
}

//Opens file and flushes map
void Configuration::writeConfig() {
    std::filebuf file;
    file.open(m_name.append(".cfg"), std::ios::out);
    std::ostream os(&file);

    for (auto iter = options.begin(); iter != options.end(); ++iter) {
        std::string key = iter->first;
        std::string val = iter->second;

        os << key << "=" << val << "\n";
    }

    os.flush();
    file.close();
}