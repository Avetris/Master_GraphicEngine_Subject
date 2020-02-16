#ifndef __MODEL_COMPONENT_H__
#define __MODEL_COMPONENT_H__ 1
#include <string>
#include "meshComponent.hpp"
#include "assimp/material.h"
#include "../renderComponent.hpp"
#include <engine/gameObject.hpp>

class aiNode;
struct aiScene;
class aiMesh;
class aiMaterial;

class ModelComponent : public RenderComponent{
public:
  /*  Model Data */
  std::vector<Texture2> textures_loaded_;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
  std::vector<MeshComponent> meshes_;
  std::string directory_;
  bool gammaCorrection_;

  /*  Functions   */
  // constructor, expects a filepath to a 3D model.
  ModelComponent(uint16_t UID, GameObject* gameObject);

  void setInitialParameters(std::string const& path, bool gamma = false);

  // draws the model, and thus all its meshes
  void render(const Shader* shader) const;
private:
  /*  Functions   */
  // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
  void loadModel(std::string const path);

  // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
  void processNode(aiNode *node, const aiScene *scene);
  MeshComponent processMesh(aiMesh *mesh, const aiScene *scene);

  // checks all material textures of a given type and loads the textures if they're not loaded yet.
  // the required info is returned as a Texture struct.
  std::vector<Texture2> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
    std::string typeName);
};

#endif