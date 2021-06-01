mod c;

pub use c::*;
use std::ops;
use vm_buffers::IntoVMBuffers;

impl Vec2f {
    /// Const value for zero value: `Vec2::new(0., 0.)`.
    pub const ZERO: Vec2f = Vec2f::new(0., 0.);

    /// Create a new vector.
    pub const fn new(x: f32, y: f32) -> Vec2f {
        Vec2f { x, y }
    }
}

impl IntoVMBuffers for Vec2f {
    fn read_from_buffers(bytes_reader: &mut vm_buffers::BytesReader) -> Self {
        Vec2f::new(bytes_reader.read_f32(), bytes_reader.read_f32())
    }

    fn write_to_buffers(&self, bytes_writer: &mut vm_buffers::BytesWriter) {
        bytes_writer.write_f32(self.x);
        bytes_writer.write_f32(self.y);
    }
}

impl Vec3f {
    /// Const value for zero value: `Vec4::new(0., 0., 0.)`.
    pub const ZERO: Vec3f = Vec3f::new(0., 0., 0.);

    /// Create a new vector.
    pub const fn new(x: f32, y: f32, z: f32) -> Vec3f {
        Vec3f { x, y, z }
    }
}

impl IntoVMBuffers for Vec3f {
    fn read_from_buffers(bytes_reader: &mut vm_buffers::BytesReader) -> Self {
        Vec3f::new(
            bytes_reader.read_f32(),
            bytes_reader.read_f32(),
            bytes_reader.read_f32(),
        )
    }

    fn write_to_buffers(&self, bytes_writer: &mut vm_buffers::BytesWriter) {
        bytes_writer.write_f32(self.x);
        bytes_writer.write_f32(self.y);
        bytes_writer.write_f32(self.z);
    }
}

impl Vec4f {
    /// Const value for zero value: `Vec4::new(0., 0., 0., 0.)`.
    pub const ZERO: Vec4f = Vec4f::new(0., 0., 0., 0.);

    /// Create a new vector.
    pub const fn new(x: f32, y: f32, z: f32, w: f32) -> Vec4f {
        Vec4f { x, y, z, w }
    }
}

impl IntoVMBuffers for Vec4f {
    fn read_from_buffers(bytes_reader: &mut vm_buffers::BytesReader) -> Self {
        Vec4f::new(
            bytes_reader.read_f32(),
            bytes_reader.read_f32(),
            bytes_reader.read_f32(),
            bytes_reader.read_f32(),
        )
    }

    fn write_to_buffers(&self, bytes_writer: &mut vm_buffers::BytesWriter) {
        bytes_writer.write_f32(self.x);
        bytes_writer.write_f32(self.y);
        bytes_writer.write_f32(self.z);
        bytes_writer.write_f32(self.w);
    }
}

impl Mat4f {
    pub const IDENT: Mat4f = Mat4f::new(
        Vec4f::new(1., 0., 0., 0.),
        Vec4f::new(0., 1., 0., 0.),
        Vec4f::new(0., 0., 1., 0.),
        Vec4f::new(0., 0., 0., 1.),
    );

    pub const fn new(c1: Vec4f, c2: Vec4f, c3: Vec4f, c4: Vec4f) -> Mat4f {
        Mat4f {
            cols: [c1, c2, c3, c4],
        }
    }
}

impl IntoVMBuffers for Mat4f {
    fn read_from_buffers(bytes_reader: &mut vm_buffers::BytesReader) -> Self {
        Mat4f::new(
            Vec4f::read_from_buffers(bytes_reader),
            Vec4f::read_from_buffers(bytes_reader),
            Vec4f::read_from_buffers(bytes_reader),
            Vec4f::read_from_buffers(bytes_reader),
        )
    }

    fn write_to_buffers(&self, bytes_writer: &mut vm_buffers::BytesWriter) {
        self.cols[0].write_to_buffers(bytes_writer);
        self.cols[1].write_to_buffers(bytes_writer);
        self.cols[2].write_to_buffers(bytes_writer);
        self.cols[3].write_to_buffers(bytes_writer);
    }
}

impl Default for Mat4f {
    fn default() -> Self {
        Mat4f::IDENT
    }
}

impl Default for Vec2f {
    fn default() -> Self {
        Vec2f::ZERO
    }
}

impl Default for Vec3f {
    fn default() -> Self {
        Vec3f::ZERO
    }
}

impl Default for Vec4f {
    fn default() -> Self {
        Vec4f::ZERO
    }
}

impl Default for CameraMatrices {
    fn default() -> Self {
        CameraMatrices {
            view_matrix: Mat4f::IDENT,
            projection_matrix: Mat4f::IDENT,
            model_matrix: Mat4f::IDENT,
            mvp_matrix: Mat4f::IDENT,
        }
    }
}

impl ops::Add<Vec2f> for Vec2f {
    type Output = Vec2f;

    fn add(self, rhs: Vec2f) -> Vec2f {
        Vec2f::new(self.x + rhs.x, self.y + rhs.y)
    }
}

impl ops::Add<Vec3f> for Vec3f {
    type Output = Vec3f;

    fn add(self, rhs: Vec3f) -> Vec3f {
        Vec3f::new(self.x + rhs.x, self.y + rhs.y, self.z + rhs.z)
    }
}

impl ops::Add<Vec4f> for Vec4f {
    type Output = Vec4f;

    fn add(self, rhs: Vec4f) -> Vec4f {
        Vec4f::new(
            self.x + rhs.x,
            self.y + rhs.y,
            self.z + rhs.z,
            self.w + rhs.w,
        )
    }
}

impl ops::AddAssign<Vec2f> for Vec2f {
    fn add_assign(&mut self, other: Self) {
        self.x += other.x;
        self.y += other.y;
    }
}

impl ops::AddAssign<Vec3f> for Vec3f {
    fn add_assign(&mut self, other: Self) {
        self.x += other.x;
        self.y += other.y;
        self.z += other.z;
    }
}

impl ops::AddAssign<Vec4f> for Vec4f {
    fn add_assign(&mut self, other: Self) {
        self.x += other.x;
        self.y += other.y;
        self.z += other.z;
        self.w += other.w;
    }
}

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

pub fn create_translate_matrix(m: Mat4f, pos: Vec3f) -> Mat4f {
    unsafe { tech_paws_vm_math_create_translate_mat(m, pos) }
}

pub fn create_rotate_matrix(m: Mat4f, rotation: f32, axis: Vec3f) -> Mat4f {
    unsafe { tech_paws_vm_math_create_rotate_mat(m, rotation, axis) }
}

pub fn create_scale_matrix(m: Mat4f, scaling: Vec3f) -> Mat4f {
    unsafe { tech_paws_vm_math_create_scale_mat(m, scaling) }
}
