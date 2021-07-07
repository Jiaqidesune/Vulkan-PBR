#include "ResourceManager.h"
#include "Mesh.h"
#include "../RHI/VulkanShader.h"
#include "../RHI/VulkanTexture.h"

#include <iostream>

using namespace RHI;

ResourceManager::ResourceManager(const VulkanRendererContext& context)
	: context(context)
{

}

Mesh* ResourceManager::getMesh(int id) const
{
	auto it = meshes.find(id);
	if (it != meshes.end())
		return it->second;

	return nullptr;
}

Mesh* ResourceManager::createCubeMesh(int id, float size)
{
	auto it = meshes.find(id);
	if (it != meshes.end())
	{
		std::cerr << "ResourceManager::loadMesh(): " << id << " is already taken by another mesh" << std::endl;
		return nullptr;
	}

	Mesh* mesh = new Mesh(context);
	mesh->createSkybox(size);

	meshes.insert(std::make_pair(id, mesh));
	return mesh;
}

Mesh* ResourceManager::loadMesh(int id, const char* path)
{
	auto it = meshes.find(id);
	if (it != meshes.end())
	{
		std::cerr << "ResourceManager::loadMesh(): " << id << " is already taken by another mesh" << std::endl;
		return nullptr;
	}

	Mesh* mesh = new Mesh(context);
	if (!mesh->loadFromFile(path))
		return nullptr;

	meshes.insert(std::make_pair(id, mesh));
	return mesh;
}

void ResourceManager::unloadMesh(int id)
{
	auto it = meshes.find(id);
	if (it == meshes.end())
		return;

	delete it->second;
	meshes.erase(it);
}

VulkanShader* ResourceManager::getShader(int id) const
{
	auto it = shaders.find(id);
	if (it != shaders.end())
		return it->second;

	return nullptr;
}

VulkanShader* ResourceManager::loadShader(int id, const char* path)
{
	auto it = shaders.find(id);
	if (it != shaders.end())
	{
		std::cerr << "ResourceManager::loadShader(): " << id << " is already taken by another shader" << std::endl;
		return nullptr;
	}

	VulkanShader* shader = new VulkanShader(context);
	if (!shader->compileFromFile(path))
		return nullptr;

	shaders.insert(std::make_pair(id, shader));
	return shader;
}

VulkanShader* ResourceManager::loadShader(int id, VulkanShaderKind kind, const char* path)
{
	auto it = shaders.find(id);
	if (it != shaders.end())
	{
		std::cerr << "ResourceManager::loadShader(): " << id << " is already taken by another shader" << std::endl;
		return nullptr;
	}

	VulkanShader* shader = new VulkanShader(context);
	if (!shader->compileFromFile(path, kind))
		return nullptr;

	shaders.insert(std::make_pair(id, shader));
	return shader;
}

void ResourceManager::unloadShader(int id)
{
	auto it = shaders.find(id);
	if (it == shaders.end())
		return;

	delete it->second;
	shaders.erase(it);
}

VulkanTexture* ResourceManager::getTexture(int id) const
{
	auto it = textures.find(id);
	if (it != textures.end())
		return it->second;

	return nullptr;
}

VulkanTexture* ResourceManager::loadTexture(int id, const char* path)
{
	auto it = textures.find(id);
	if (it != textures.end())
	{
		std::cerr << "ResourceManager::loadTexture(): " << id << " is already taken by another texture" << std::endl;
		return nullptr;
	}

	VulkanTexture* texture = new VulkanTexture(context);
	if (!texture->loadFromFile(path))
		return nullptr;

	textures.insert(std::make_pair(id, texture));
	return texture;
}

void ResourceManager::unloadTexture(int id)
{
	auto it = textures.find(id);
	if (it == textures.end())
		return;

	delete it->second;
	textures.erase(it);
}