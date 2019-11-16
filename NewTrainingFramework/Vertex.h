#pragma once
#include "../Utilities/utilities.h" 

struct Vertex2
{
	Vector3 pos;
	Vector3 color;
};

struct Vertex
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv, uvBlend;

public:
	Vertex(const Vertex &a) : pos(a.pos), norm(a.norm), binorm(a.binorm), tgt(a.tgt), uv(a.uv.x, a.uv.y), uvBlend(a.uvBlend.x, a.uvBlend.y) {}
	Vertex(Vector3 &a, Vector3 &b, Vector3 &c, Vector3 &d, Vector2 &e) : pos(a.x, a.y, a.z), norm(b.x, b.y, b.z), binorm(c.x, c.y, c.z), tgt(d.x, d.y, d.z), uv(e.x, e.y) {}
	Vertex(Vector3 &a, Vector3 &b, Vector3 &c, Vector3 &d, Vector2 &e, Vector2 &f) : pos(a.x, a.y, a.z), norm(b.x, b.y, b.z), binorm(c.x, c.y, c.z), tgt(d.x, d.y, d.z), uv(e.x, e.y), uvBlend(f.x, f.y) {}
	Vertex(Vector3 &a) : pos(a.x, a.y, a.z) {}
	Vertex();
};