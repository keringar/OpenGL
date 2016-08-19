#include "Util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <random>

/*///////////////
//UTILITY CLASS//
///////////////*/
std::string Util::getTime(){
    char buffer[20];

    auto rawTime = time(nullptr);
    auto timeInfo = localtime(&rawTime);
    strftime(buffer, 80, "%c", timeInfo);
    return std::string(buffer).append("\n");
}

int Util::randomInt() {
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    //Defaults to all possible ints
    std::uniform_int_distribution<int> dist(INT32_MIN, INT32_MAX);
    return dist(generator);
}


/*///////////////
//LOGGING CLASS//
///////////////*/
bool Log::firstRun = true;

//Channels has a default parameter of none
void Log::log(const std::string &data, Channels c) {
    if (firstRun) {
        firstRun = false;
        std::remove("output.log");

        Log::log(Util::getTime(), Log::Channels::None);
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

/*////////////
//FILE CLASS//
////////////*/
std::string File::readString(const std::string &file_path) {
    std::ifstream in(file_path);

    std::stringstream buffer;
    buffer << in.rdbuf();

    return buffer.str();
}

void File::writeFile(const std::string &file_path, const std::string &contents) {
    std::ofstream out(file_path);

    out << contents;
}

/*/////////////////////
//CONFIGURATION CLASS//
/////////////////////*/
Configuration::Configuration(std::string name) : m_name{name} {
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

std::string Configuration::getWithDefault(std::string key, std::string defaultValue) {
    if (get(key) == "") {
        return setValue(key, defaultValue);
    }

    return get(key);
}

//Returns value
std::string Configuration::setValue(std::string key, std::string value) {
    options[key] = value;
    writeConfig();
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
    std::string tmp = m_name;
    file.open(tmp.append(".cfg"), std::ios::out);
    std::ostream os(&file);

    for (auto iter = options.begin(); iter != options.end(); ++iter) {
        std::string key = iter->first;
        std::string val = iter->second;

        os << key << "=" << val << "\n";
    }

    os.flush();
    file.close();
}