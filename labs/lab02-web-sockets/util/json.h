#ifndef UTIL_JSON_H_
#define UTIL_JSON_H_

#include "WebServer.h"

class JsonObject;
class JsonArray;


class JsonValue {
public:
    JsonValue(picojson::value& val) : val(val) {}
    void operator=(int x);
    void operator=(const std::string& str);
    operator int();
    operator double();
    operator std::string();
    std::string ToString() const;
    operator JsonObject();
    operator JsonArray();
    void operator=(const JsonObject& obj);
    void operator=(const JsonArray& obj);
private:
    template<typename T>
    T& As();
    picojson::value& val;
};

class JsonObject {
public:
    JsonObject(picojson::object& obj) : obj(obj) {}
    std::vector<std::string> GetKeys();
    JsonValue operator[](const std::string& key);
    std::string ToString() const;
    const picojson::object& GetObject() const { return obj; }
private:
    picojson::object& obj;
};

class JsonArray {
public:
    JsonArray(picojson::array& array) : array(array) {}
    JsonValue operator[](int index);
    int Size();
    std::string ToString() const;
    const picojson::array& GetArray() const { return array; }
private:
    picojson::array& array;
};


class JsonSession : public JSONSession {
public:
    /// Initializes server
    JsonSession() {
    }

    /// Destructor
    virtual ~JsonSession() {
    }

    /// Receives JSON from the web server
    void receiveJSON(picojson::value& val) {
        picojson::object data = val.get<picojson::object>();
        std::string cmd = data["command"].get<std::string>();
        picojson::object returnValue;
        returnValue["id"] = data["id"];
        JsonObject dataObject(data);
        JsonObject returnValueObject(returnValue);
        ReceiveCommand(cmd, dataObject, returnValueObject);
        picojson::value retVal(returnValue);
        sendJSON(retVal);
    }

    /// Handles specific commands from the web server
    virtual void ReceiveCommand(const std::string& cmd, JsonObject& data, JsonObject& returnValue) = 0;
};



// ----------------------- Implementation -----------------------------

inline void JsonValue::operator=(int x) {
    val = picojson::value((double)x);
}
inline void JsonValue::operator=(const std::string& str) {
    val = picojson::value(str);
}
inline JsonValue::operator int() {
    return val.get<double>();
}
inline JsonValue::operator double() {
    return val.get<double>();
}
inline JsonValue::operator std::string() {
    return val.get<std::string>();
}

inline std::string JsonValue::ToString() const {
    return val.serialize();
}

inline JsonValue::operator JsonObject() {
    return JsonObject(As<picojson::object>());
}

inline JsonValue::operator JsonArray() {
    return JsonArray(As<picojson::array>());
}

inline void JsonValue::operator=(const JsonObject& obj) {
    val = picojson::value(obj.GetObject());
}

inline void JsonValue::operator=(const JsonArray& array) {
    val = picojson::value(array.GetArray());
}

template<typename T>
inline T& JsonValue::As() {
    if (!val.is<T>()) {
        val = picojson::value(T());
    }
    return val.get<T>();
}

inline std::vector<std::string> JsonObject::GetKeys() {
    std::vector<std::string> keys;
    for (auto it = obj.begin(); it != obj.end(); it++) {
        keys.push_back(it->first);
    }
    return keys;
}

inline JsonValue JsonObject::operator[](const std::string& key) {
    return JsonValue(obj[key]);
}

inline std::string JsonObject::ToString() const {
    return picojson::value(obj).serialize();
}

inline std::ostream& operator<<(std::ostream& os, const JsonObject& obj) {
    os << obj.ToString();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
    os << array.ToString();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const JsonValue& val) {
    os << val.ToString();
    return os;
}

inline JsonValue JsonArray::operator[](int index) {
    if (index >= array.size()) {
        array.resize(index+1);
    }
    return JsonValue(array[index]);
}

inline int JsonArray::Size() { return array.size(); }

inline std::string JsonArray::ToString() const {
    return picojson::value(array).serialize();
}


#endif