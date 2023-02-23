#pragma once
#include "../Object/Object.h"

namespace Engine
{
    class AssetDataBase : public Object
    {
        DECLARE_CLASS_INFO(AssetDataBase, Object)
#pragma region f/p
    private:
        static inline std::map<Object*, std::string> AllObjectsPath = std::map<Object*, std::string>();
#pragma endregion f/p
#pragma region methods
    public:
        static void CreateAsset(Object* _asset, PrimaryType::String _path);
        static std::vector<Object*> LoadAllAssets();
        static std::string GetAssetPath(Object* _obj);
#pragma endregion methods
    };
}
