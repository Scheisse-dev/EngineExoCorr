#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace Engine::PrimaryType
{
    struct EnumSupportBase
    {
        static void Trim(std::string& _str)
        {
            size_t _startPos = 0;
            const std::string& _from = " ";
            const std::string& _to = "";
            while ((_startPos = _str.find(_from, _startPos)) != std::string::npos)
            {
                _str.replace(_startPos, _from.length(), _to);
                _startPos += _to.length();
            }
        }

        static std::map<int, std::string> Split(const std::string& _str)
        {
            std::stringstream _stream = std::stringstream(_str);
            std::string _item = "";
            std::map<int, std::string> _result = std::map<int, std::string>();
            int _currentIndex = -1;
            while (std::getline(_stream, _item, ','))
            {
                size_t _pos = _item.find_first_of('=');
                if (_pos != std::string::npos)
                {
                    _currentIndex = std::stoi(_item.substr(_pos + 2));
                    _item.erase(_pos);
                }
                else _currentIndex++;
                Trim(_item);
                _result.insert(std::pair(_currentIndex, _item));
            }
            return _result;
        }
    };

#define ENUM(Name, ...) \
    enum class Name : uint8_t { __VA_ARGS__ }; \
    struct Name##Support : Engine::PrimaryType::EnumSupportBase\
    {\
        private:\
            static inline std::map<int, std::string> values = Split(#__VA_ARGS__);\
        public:\
            static constexpr std::string GetName(Name _value)\
            {\
                const int _index = (int)_value;\
                return values[_index];\
            }\
            static std::vector<Name> Values() \
            {\
                std::vector<Name> _result = std::vector<Name>();\
                for (std::pair<int, std::string> _value : values)\
                    _result.push_back((Name)_value.first);\
                return _result;\
            }\
    };\
    inline std::string operator*(const Name& _value)\
    {\
        return Name##Support::GetName(_value);\
    }
}
