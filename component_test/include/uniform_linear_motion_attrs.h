/**
* @file
* @brief 包含所有匀速直线运动属性的头文件.
* @author ruoxi
*
* 定义了所有的匀速直线运动属性.
*/

#ifndef __USE_UNIFORM_LINEAR_MOTION_ATTRS__
#error uniform_linear_motion_attrs.h is wrongly included.
#endif // __USE_UNIFORM_LINEAR_MOTION_ATTRS__
#undef __USE_UNIFORM_LINEAR_MOTION_ATTRS__

DEFINE_ATTR(ATTR_NAME, "Name of uniform linear motion.")
DEFINE_ATTR(ATTR_VELOCITY, "Velocity of uniform linear motion.")
DEFINE_ATTR(ATTR_ACCELERATION, "Acceleration of uniform linear motion.")
