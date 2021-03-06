#ifndef __MODEL_H__
#define __MODEL_H__

#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <string>
#include <vector>

using glm::mat3x2;
using glm::mat3;
using glm::ivec3;
using glm::vec2;
using glm::vec3;

typedef struct
{
    ivec3 vi  = {-1, -1, -1}; // vertex indices
    ivec3 vti = {-1, -1, -1}; // vertex texture indices
    ivec3 vni = {-1, -1, -1}; // vertex normal indices
}
face;

typedef struct
{
    std::vector<vec3> verts;
    std::vector<vec3> vert_norms;
    std::vector<vec2> text_verts;
    std::vector<face> faces;

    mat3 get_verts(const face& f) const;
    mat3x2 get_texture_verts(const face& face) const;
    mat3 get_vertex_normals(const face& face) const;
} model;

std::unique_ptr<model> load_model(const std::string& file);
void test_print_model(const model& m);

glm::vec3 face_normal(glm::mat3 face_verts);


#endif //__MODEL_H__

