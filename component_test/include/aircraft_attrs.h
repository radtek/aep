/**
* @file
* @brief �������з��������Ե�ͷ�ļ�.
* @author ruoxi
*
* ���������еķ���������.
*/

#ifndef __USE_AIRCRAFT_ATTRS__
#error aircraft_attrs.h is wrongly included.
#endif // __USE_AIRCRAFT_ATTRS__
#undef __USE_AIRCRAFT_ATTRS__

DEFINE_ATTR(ATTR_START_COORDINATE, "Start coordinate of aircraft.")
DEFINE_ATTR(ATTR_START_VELOCITY, "Start velocity of aircraft.")
DEFINE_ATTR(ATTR_CURRENT_COORDINATE, "Current coordinate of aircraft.")
DEFINE_ATTR(ATTR_CURRENT_VELOCITY, "Current velocity of aircraft.")
DEFINE_ATTR(ATTR_MOTION, "Motion of aircraft.")
