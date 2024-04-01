#include "Camera.h"

// TODO: fill up the following function properly
void Camera::set_rotation(const glm::quat& _q)
{
  glm::mat4 q = glm::mat3_cast(_q);
  front_dir_ = -q[2];
  up_dir_ = q[1];
  right_dir_ = q[0];
}

// TODO: re-write the following function properly
const glm::quat Camera::get_rotation() const
{
  glm::mat4 r = glm::mat4(
    glm::vec4(right_dir_, 0.0f),
    glm::vec4(up_dir_, 0.0f),
    glm::vec4(-front_dir_, 0.0f),
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
  );
  return glm::quat_cast(r);
}

// TODO: fill up the following function properly
void Camera::set_pose(const glm::quat& _q, const glm::vec3& _t)
{
  set_rotation(_q);
  set_position(_t);
}

// TODO: fill up the following function properly
void Camera::get_pose(glm::quat& _q, glm::vec3& _t) const
{
  _q = get_rotation();
  _t = position();
}

// TODO: rewrite the following function properly
const glm::mat4 Camera::get_pose() const
{
  glm::mat4 p = glm::mat4(
    glm::vec4(right_dir_, 0.0f),
    glm::vec4(up_dir_, 0.0f),
    glm::vec4(-front_dir_, 0.0f),
    glm::vec4(position_, 1.0f)
  );
  return p;
}

// TODO: fill up the following function properly
void Camera::set_pose(const glm::mat4& _frame)
{
  // +x_cam: right direction of the camera    (it should be a unit vector whose length is 1)
  right_dir_ = _frame[0] ; // +x
  // +y_cam: up direction of the camera       (it should be a unit vector whose length is 1)
  up_dir_    = _frame[1] ;    // +y
  // -z_cam: front direction of the camera    (it should be a unit vector whose length is 1)
  front_dir_ = -_frame[2] ;    // -z
  // pos_cam: position of the camera
  position_  = _frame[3] ;    // pos
}

// TODO: fill up the following function properly
void Camera::set_pose(const glm::vec3& _pos, const glm::vec3& _at, const glm::vec3& _up_dir)
{
  // front_dir_ = ..... ;    // -z_cam direction
  // right_dir_ = ..... ;    // +x_cam direction
  // up_dir_    = ..... ;    // +y_cam direction
  glm::mat4 v_inverse = glm::lookAt(
    _pos,
    _at,
    _up_dir
  );
  right_dir_ = glm::vec3(v_inverse[0][0], v_inverse[1][0], v_inverse[2][0]);
  up_dir_ = glm::vec3(v_inverse[0][1], v_inverse[1][1], v_inverse[2][1]);
  front_dir_ = -glm::vec3(v_inverse[0][2], v_inverse[1][2], v_inverse[2][2]);

  // position_  = ..... ;      // pos
  glm::vec3 rot_inversePos = -glm::vec3(v_inverse[3][0], v_inverse[3][1], v_inverse[3][2]);
  position_ = glm::mat3(right_dir_, up_dir_, -front_dir_) * rot_inversePos;
}

// TODO: rewrite the following function properly
const glm::mat4 Camera::get_view_matrix() const
{
  glm::mat4 view = glm::transpose(glm::mat4_cast(get_rotation())) * glm::translate(glm::mat4(1.0f), -position_);
  return view;
}

// TODO: rewrite the following function properly
const glm::mat4 Camera::get_projection_matrix() const
{
  // TODO: Considering the followings,
  //       You must return a proper projection matrix
  //       i) camera mode: it can be either kOrtho or kPerspective
  //       ii) zoom-in/-out: if the camera mode is kOrtho,
  //                         utilize ortho_scale_ for zoom-in/-out
  //                         if the camera mode is kPerspective,
  //                         utilize fovy_ for zoom-in/-out
  //       iii) aspect ratio: utilize aspect_ in the both camera modes
  //       iv) near/far clipping planes: utilize near_, far_
  if (mode_ == kOrtho){
     return glm::ortho(
       -ortho_scale_ * aspect_, ortho_scale_ * aspect_,
       -ortho_scale_, ortho_scale_,
        near_, far_);
  }
  else{
    return glm::perspective(glm::radians(fovy_), aspect_, near_, far_);
  }
}

// TODO: fill up the following functions properly
void Camera::move_forward(float delta)
{
  //glm::vec3 newPosition = position_ - delta * right_dir_;
  //set_position(newPosition);
  position_ += delta * front_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_backward(float delta)
{
  position_ -= delta * front_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_left(float delta)
{
  position_ -= delta * right_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_right(float delta)
{
  position_ += delta * right_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_up(float delta)
{
  position_ += delta * up_dir_;
}

// TODO: fill up the following functions properly
void Camera::move_down(float delta)
{
  position_ -= delta * up_dir_;
}
