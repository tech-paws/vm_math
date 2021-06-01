#include "vm_math.hpp"
#include "vm_glm_adapter.hpp"
#include <glm/gtc/matrix_transform.hpp>

extern "C" CameraMatrices tech_paws_vm_math_create_ortho_camera_matrices(const OthroCameraTransforms transforms) {
    const glm::vec3 eye = glm::vec3(glm_vec2(transforms.position), 1.0f);
    const glm::vec3 target = glm::vec3(glm_vec2(transforms.position), 0.0f);
    const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    glm::mat4 model_matrix;
    glm::mat4 mvp_matrix;

    view_matrix = glm::lookAt(eye, target, up);
    projection_matrix = glm::ortho(
        0.0f, transforms.viewport_size.x,
        0.0f, transforms.viewport_size.y,
        0.0f, 10.0f
    );

    if (transforms.zoom > 1.0f) {
        model_matrix = glm::scale(
            glm::mat4(),
            glm::vec3(transforms.zoom, transforms.zoom, 1.0f)
        );
    } else {
        model_matrix = glm::mat4(1);
    }

    mvp_matrix = projection_matrix * model_matrix * view_matrix;

    CameraMatrices camera_matrices;

    vm_mat4f(camera_matrices.view_matrix, view_matrix);
    vm_mat4f(camera_matrices.projection_matrix, projection_matrix);
    vm_mat4f(camera_matrices.model_matrix, model_matrix);
    vm_mat4f(camera_matrices.mvp_matrix, mvp_matrix);

    return camera_matrices;
}

extern "C" Mat4f tech_paws_vm_math_transforms_create_2d_model_matrix(const Transforms2D transforms) {
    const auto translate_matrix = glm::translate(
        glm::mat4(1),
        glm::vec3(glm_vec2(transforms.position), 0.0f)
    );

    const auto rotate_matrix = glm::rotate(
        glm::mat4(1),
        transforms.rotation,
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    const auto scale_matrix = glm::scale(
        glm::mat4(1),
        glm::vec3(glm_vec2(transforms.scaling), 1.0f)
    );

    return vm_mat4f(translate_matrix * rotate_matrix * scale_matrix);
}

extern "C" Mat4f tech_paws_vm_math_create_translate_mat(const Mat4f m, const Vec3f pos) {
    const auto translate_matrix = glm::translate(glm_mat4(m), glm_vec3(pos));
    return vm_mat4f(translate_matrix);
}

extern "C" Mat4f tech_paws_vm_math_create_rotate_mat(const Mat4f m, const float rotation, const Vec3f axis) {
    const auto rotate_matrix = glm::rotate(glm_mat4(m), rotation, glm_vec3(axis));
    return vm_mat4f(rotate_matrix);
}

extern "C" Mat4f tech_paws_vm_math_create_scale_mat(const Mat4f m, const Vec3f scaling) {
    const auto scale_matrix = glm::scale(glm_mat4(m), glm_vec3(scaling));
    return vm_mat4f(scale_matrix);
}

extern "C" Mat4f tech_paws_vm_math_mat4_to_mat4_mul(const Mat4f m1, const Mat4f m2) {
    return vm_mat4f(glm_mat4(m1) * glm_mat4(m2));
}

extern "C" Vec4f tech_paws_vm_math_mat4_to_vec4_mul(const Mat4f m, const Vec4f v) {
    return vm_vec4f(glm_mat4(m) * glm_vec4(v));
}

extern "C" Vec4f tech_paws_vm_math_vec4_to_mat4_mul(const Vec4f v, const Mat4f m) {
    return vm_vec4f(glm_vec4(v) * glm_mat4(m));
}
