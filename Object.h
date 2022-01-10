#pragma once
#include <vector>
#include <string>
#include "Vector.h"
#include "Texture.h"

using namespace std;

struct Vertex
{
	Vector position;
	Vector texcoord;

	Vertex(Vector, Vector = Vector());
};

struct Mesh
{
	vector<Vertex> vertices;
	vector<vector<unsigned int>> faces;
	Texture texture;

	Mesh(vector<Vertex>, vector<vector<unsigned int>>, Texture = Texture());

	void Render();
};

struct Object
{
	inline static vector<Object*> all;

	vector<Mesh> meshes;

	double scale;

	Object(Mesh);
	Object(string, double = 1);

	void Render();
};