#pragma once

#define DEFINE_TO_STRING(enum_name, ...) std::string ToString(enum_name s){\
    static const std::string LABEL[] = { __VA_ARGS__ };\
    return LABEL[static_cast<int>(s)];\
}

#define DEFINE_TO_ENUM(enum_name, ...) enum_name To##enum_name(const std::string& value) {\
    static const std::string LABEL[] = { __VA_ARGS__ };\
    auto it = std::find(std::begin(LABEL), std::end(LABEL), value);\
    if (it == std::end(LABEL)) throw std::bad_cast();\
    auto index = std::distance(std::begin(LABEL), it);\
    return static_cast<enum_name>(index);\
}