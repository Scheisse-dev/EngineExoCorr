#pragma once
#include "../Object/Object.h"

namespace Engine
{
    class File : public Object
    {
        DECLARE_CLASS_INFO(File, Object)
#pragma region f/p
    private:
        std::string path = "";
#pragma endregion f/p
#pragma region constructor
    public:
        File() = delete;
        File(const std::string& _path);
#pragma endregion constructor
#pragma region methods
    public:
        std::vector<PrimaryType::String> ReadAllLines() const;
#pragma endregion methods
    };
}
