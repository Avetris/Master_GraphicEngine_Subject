#include <engine\managers\materialManager.hpp>

Material* MaterialManager::getMaterial(const std::string pathDiffuse, const std::string pathSpecular, const std::string pathNormal, int shininess)
{
	Material* material = nullptr;
	bool exist = false;
	bool isNew[3] = { false };
	Texture* textDiffuse = getTexture(pathDiffuse, isNew[0]);
	Texture* textSpecular = getTexture(pathSpecular, isNew[1]);
	Texture* textNormal = getTexture(pathNormal, isNew[2]);
	if (!isNew[0] && !isNew[1] && !isNew[2]) {
		for (auto it = _usedMaterials.begin(); it < _usedMaterials.end() && !exist; it++) {
			if ((*it)->sameMaterial(textDiffuse, textSpecular, textNormal, shininess)) {
				exist = true;
				material = it->get();
			}
		}
	}
	if (!exist) {
		if (textNormal) {
			_usedMaterials.push_back(std::make_unique<Material>(textDiffuse, textSpecular, textNormal, shininess));
		}
		else {
			_usedMaterials.push_back(std::make_unique<Material>(textDiffuse, textSpecular, shininess));
		}
		material = _usedMaterials.back().get();
	}
	return material;
}

Texture* MaterialManager::getTexture(std::string path, bool& isNew)
{
	Texture* texture = nullptr;
	if (!path.empty()) {
		auto exist = _usedTextures.find(path);
		if (exist != _usedTextures.end()) {
			texture = exist->second.get();
			isNew = false;
		}
		else {
			_usedTextures.insert({ path, std::make_unique<Texture>(path.c_str(), GPU::Format::RGB)});
			auto el = _usedTextures.find(path);
			texture = el->second.get();
			isNew = true;
		}
	}
	return texture;
}
