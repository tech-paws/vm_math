#pragma once

struct Vec2f {
    float x;
    float y;
};

struct Vec3f {
    float x;
    float y;
    float z;
};

struct Vec4f {
    float x;
    float y;
    float z;
    float w;
};

struct Mat4f {
    Vec4f cols[4];
};

struct Rect {
    Vec2f pos;
    Vec2f size;
};

struct CameraMatrices {
    Mat4f view_matrix;
    Mat4f projection_matrix;
    Mat4f model_matrix;
    Mat4f mvp_matrix;
};

struct OthroCameraTransforms {
    Vec2f viewport_size;
    Vec2f position;
    float zoom;
};

struct Transforms2D {
    Vec2f position;
    Vec2f scaling;
    float rotation;
};

inline float const* tech_paws_vm_math_vec3fptr(Vec3f const* vec) {
    return &vec->x;
}

inline float const* tech_paws_vm_math_vec2fptr(Vec2f const* vec) {
    return &vec->x;
}

inline float const* tech_paws_vm_math_vec4fptr(Vec4f const* vec) {
    return &vec->x;
}

inline float const* tech_paws_vm_math_mat4fptr(Mat4f const* mat) {
    return &mat->cols[0].x;
}

inline float const* tech_paws_vm_math_vec4fptr(Vec4f const& vec) {
    return &vec.x;
}

inline float const* tech_paws_vm_math_mat4fptr(Mat4f const& mat) {
    return &mat.cols[0].x;
}

extern "C" CameraMatrices tech_paws_vm_math_create_ortho_camera_matrices(const OthroCameraTransforms transforms);

extern "C" Mat4f tech_paws_vm_math_transforms_create_2d_model_matrix(const Transforms2D transforms);

extern "C" Mat4f tech_paws_vm_math_create_translate_mat(const Mat4f m, const Vec3f pos);

extern "C" Mat4f tech_paws_vm_math_create_rotate_mat(const Mat4f m, const float rotation, const Vec3f axis);

extern "C" Mat4f tech_paws_vm_math_create_scale_mat(const Mat4f m, const Vec3f scaling);

extern "C" Mat4f tech_paws_vm_math_mat4_to_mat4_mul(const Mat4f m1, const Mat4f m2);

extern "C" Vec4f tech_paws_vm_math_mat4_to_vec4_mul(const Mat4f m, const Vec4f v);

extern "C" Vec4f tech_paws_vm_math_vec4_to_mat4_mul(const Vec4f v, const Mat4f m);
