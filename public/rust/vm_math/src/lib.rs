pub mod vm_math;

use std::ops;
use vm_math::*;

impl ops::Mul<Mat4f> for Mat4f {
    type Output = Mat4f;

    fn mul(self, rhs: Mat4f) -> Mat4f {
        unsafe { tech_paws_vm_math_mat4_to_mat4_mul(self, rhs) }
    }
}

impl ops::Mul<Vec4f> for Mat4f {
    type Output = Vec4f;

    fn mul(self, rhs: Vec4f) -> Vec4f {
        unsafe { tech_paws_vm_math_mat4_to_vec4_mul(self, rhs) }
    }
}

impl ops::Mul<Mat4f> for Vec4f {
    type Output = Vec4f;

    fn mul(self, rhs: Mat4f) -> Vec4f {
        unsafe { tech_paws_vm_math_vec4_to_mat4_mul(self, rhs) }
    }
}

pub fn create_2d_model_matrix(transforms: Transforms2D) -> Mat4f {
    unsafe { tech_paws_vm_math_transforms_create_2d_model_matrix(transforms) }
}

pub fn create_ortho_camera_matrices(transforms: OthroCameraTransforms) -> CameraMatrices {
    unsafe { tech_paws_vm_math_create_ortho_camera_matrices(transforms) }
}
