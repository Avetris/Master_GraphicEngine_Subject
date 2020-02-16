#ifndef __MATERIAL_MANAGER_H__
#define __MATERIAL_MANAGER_H__

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <engine\material.hpp>
#include <engine\texture.hpp>
#include <glm/glm.hpp>
#include <memory>

class MaterialManager{
    public:
        static MaterialManager* instance() {
            static MaterialManager mmInstance;
            return &mmInstance;
        }
        
        Material* getMaterial(const std::string pathDiffuse, const std::string pathSpecular, const std::string pathNormal, int shininess);
        Texture* getTexture(std::string path, bool& isNew);

    private:
        std::vector<std::unique_ptr<Material>> _usedMaterials;
        std::unordered_map<std::string, std::unique_ptr<Texture>> _usedTextures;
};
#endif
    