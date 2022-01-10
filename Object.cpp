#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include "Object.h"

typedef filesystem::path Path;


Vertex::Vertex(Vector vertexPosition, Vector textureCoordinate)
{
    position = vertexPosition;
    texcoord = textureCoordinate;
}


Mesh::Mesh(vector<Vertex> vertexList, vector<vector<unsigned int>> faceList, Texture meshTexture)
{
    vertices = vertexList;
    faces = faceList;
    texture = meshTexture;
}

void Mesh::Render()
{
    glBindTexture(GL_TEXTURE_2D, texture.id);
    for (vector<unsigned int> face : faces)
    {
        glBegin(GL_POLYGON);
        for (unsigned int i : face)
        {
            glColor3d(1, 1, 1);
            glTexCoord2d(vertices[i].texcoord.x, vertices[i].texcoord.y);
            glVertex3d(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
        }
        glEnd();
    }
}

Mesh readMesh(aiMesh* mesh, const aiScene* scene, string path = "")
{
    vector<Vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vector position(mesh->mVertices[i].x, mesh->mVertices[i].z, mesh->mVertices[i].y);
        Vector texcoord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        vertices.push_back(Vertex(position, texcoord));
    }

    vector<vector<unsigned int>> faces;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        vector<unsigned int> face;
        for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            face.push_back(mesh->mFaces[i].mIndices[j]);
        faces.push_back(face);
    }

    Texture texture;
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString file;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &file);
        texture = Texture(path + file.C_Str());
    }

    return Mesh(vertices, faces, texture);
}


Object::Object(Mesh mesh) : scale(1)
{
    meshes.push_back(mesh);
    Object::all.push_back(this);
}

Object::Object(string file, double modelScale) : scale(modelScale)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file, aiProcess_FlipUVs);
    string path = ((Path)file).remove_filename().string();
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        meshes.push_back(readMesh(scene->mMeshes[i], scene, path));
    Object::all.push_back(this);
}



void Object::Render()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScaled(scale, scale, scale);
    for (Mesh mesh : meshes)
        mesh.Render();
    glPopMatrix();
}