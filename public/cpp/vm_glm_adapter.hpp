#pragma once

#include "vm_math.hpp"
#include <glm/gtc/matrix_transform.hpp>

inline glm::vec2 vm_glm_vec2(Vec2f const& vec) {
    return glm::vec2(vec.x, vec.y);
}

inline glm::vec3 vm_glm_vec3(Vec3f const& vec) {
    return glm::vec3(vec.x, vec.y, vec.z);
}

inline glm::vec4 vm_glm_vec4(Vec4f const& vec) {
    return glm::vec4(vec.x, vec.y, vec.z, vec.w);
}

inline glm::mat4 vm_glm_mat4(Mat4f const& mat) {
    return glm::mat4(
        glm::vec4(mat.cols[0].x, mat.cols[1].x, mat.cols[2].x, mat.cols[3].x),
        glm::vec4(mat.cols[0].y, mat.cols[1].y, mat.cols[2].y, mat.cols[3].y),
        glm::vec4(mat.cols[0].z, mat.cols[1].z, mat.cols[2].z, mat.cols[3].z),
        glm::vec4(mat.cols[0].w, mat.cols[1].w, mat.cols[2].w, mat.cols[3].w)
    );
}

inline Vec2f vm_vec2f(float x, float y) {
    return Vec2f { .x = x, .y = y };
}

inline Vec3f vm_vec3f(float x, float y, float z) {
    return Vec3f { .x = x, .y = y, .z = z };
}

inline Vec4f vm_vec4f(float x, float y, float z, float w) {
    return Vec4f { .x = x, .y = y, .z = z, .w = w };
}

inline Vec2f vm_vec2f(glm::vec2 const& glm_vec) {
    return vm_vec2f(glm_vec.x, glm_vec.y);
}

inline Vec3f vm_vec3f(glm::vec3 const& glm_vec) {
    return vm_vec3f(glm_vec.x, glm_vec.y, glm_vec.z);
}

inline Vec4f vm_vec4f(glm::vec4 const& glm_vec) {
    return vm_vec4f(glm_vec.x, glm_vec.y, glm_vec.z, glm_vec.w);
}

inline Mat4f vm_mat4f(Vec4f c1, Vec4f c2, Vec4f c3, Vec4f c4) {
    return Mat4f { .cols = { c1, c2, c3, c4 } };
}

inline Mat4f vm_mat4f(glm::mat4 const& glm_mat) {
    return vm_mat4f(
        vm_vec4f(glm_mat[0].x, glm_mat[1].x, glm_mat[2].x, glm_mat[3].x),
        vm_vec4f(glm_mat[0].y, glm_mat[1].y, glm_mat[2].y, glm_mat[3].y),
        vm_vec4f(glm_mat[0].z, glm_mat[1].z, glm_mat[2].z, glm_mat[3].z),
        vm_vec4f(glm_mat[0].w, glm_mat[1].w, glm_mat[2].w, glm_mat[3].w)
    );
}

inline void vm_vec4f(Vec4f& vec, glm::vec4 const& glm_vec) {
    vec.x = glm_vec.x;
    vec.y = glm_vec.y;
    vec.z = glm_vec.z;
    vec.w = glm_vec.w;
}

inline void vm_mat4f(Mat4f& mat, glm::mat4 const& glm_mat) {
    mat.cols[0] = vm_vec4f(glm_mat[0].x, glm_mat[1].x, glm_mat[2].x, glm_mat[3].x);
    mat.cols[1] = vm_vec4f(glm_mat[0].y, glm_mat[1].y, glm_mat[2].y, glm_mat[3].y);
    mat.cols[2] = vm_vec4f(glm_mat[0].z, glm_mat[1].z, glm_mat[2].z, glm_mat[3].z);
    mat.cols[3] = vm_vec4f(glm_mat[0].w, glm_mat[1].w, glm_mat[2].w, glm_mat[3].w);
}
