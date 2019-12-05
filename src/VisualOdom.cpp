// -*- C++ -*-
/*!
 * @file  VisualOdom.cpp
 * @brief Visual Odometry RTC with RGB-D Camera
 * @date $Date$
 *
 * $Id$
 */

#include "VisualOdom.h"


// Module specification
// <rtc-template block="module_spec">
static const char* visualodom_spec[] =
  {
    "implementation_id", "VisualOdom",
    "type_name",         "VisualOdom",
    "description",       "Visual Odometry RTC with RGB-D Camera",
    "version",           "1.0.0",
    "vendor",            "Maika Iwai, Robot System Design Laboratory, Meijo University",
    "category",          "ImageProcessing",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.SensorNumber", "0",

    // Widget
    "conf.__widget__.SensorNumber", "text",
    // Constraints

    "conf.__type__.SensorNumber", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
VisualOdom::VisualOdom(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pose3DQuaternionOut("Pose3DQuaternion", m_pose3DQuaternion)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
VisualOdom::~VisualOdom()
{
}



RTC::ReturnCode_t VisualOdom::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("Pose3DQuaternion", m_pose3DQuaternionOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("SensorNumber", m_SensorNumber, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VisualOdom::onActivated(RTC::UniqueId ec_id)
{
  vo.Init(RS_T265);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VisualOdom::onDeactivated(RTC::UniqueId ec_id)
{
  vo.Close();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VisualOdom::onExecute(RTC::UniqueId ec_id)
{
  p3dq = vo.GetData();

  //出力用変数へ位置姿勢データを格納
  m_pose3DQuaternion.pose3D.position.x = p3dq.trans.x;
  m_pose3DQuaternion.pose3D.position.y = p3dq.trans.y;
  m_pose3DQuaternion.pose3D.position.z = p3dq.trans.z;
  m_pose3DQuaternion.quaternion.x = p3dq.rot.x;
  m_pose3DQuaternion.quaternion.y = p3dq.rot.y;
  m_pose3DQuaternion.quaternion.z = p3dq.rot.z;
  m_pose3DQuaternion.quaternion.w = p3dq.rot.w;
  
  //位置情報を端末に表示
  printf("\rposition(x, y, z) = (%5.2f, %5.2f, %5.2f)", m_pose3DQuaternion.pose3D.position.x, m_pose3DQuaternion.pose3D.position.y, m_pose3DQuaternion.pose3D.position.z);
  
  //出力
  m_pose3DQuaternionOut.write();
  
  return RTC::RTC_OK;
}


extern "C"
{
 
  void VisualOdomInit(RTC::Manager* manager)
  {
    coil::Properties profile(visualodom_spec);
    manager->registerFactory(profile,
                             RTC::Create<VisualOdom>,
                             RTC::Delete<VisualOdom>);
  }
  
};


