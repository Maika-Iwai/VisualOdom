// -*- C++ -*-
/*!
 * @file  VisualOdomTest.cpp
 * @brief Visual Odometry RTC with RGB-D Camera
 * @date $Date$
 *
 * $Id$
 */

#include "VisualOdomTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* visualodom_spec[] =
  {
    "implementation_id", "VisualOdomTest",
    "type_name",         "VisualOdomTest",
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
VisualOdomTest::VisualOdomTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pose3DQuaternionOut("Pose3DQuaternion", m_pose3DQuaternion)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
VisualOdomTest::~VisualOdomTest()
{
}



RTC::ReturnCode_t VisualOdomTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Pose3DQuaternion", m_pose3DQuaternionIn);
  
  // Set OutPort buffer
  
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

/*
RTC::ReturnCode_t VisualOdomTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VisualOdomTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VisualOdomTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t VisualOdomTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VisualOdomTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VisualOdomTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t VisualOdomTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VisualOdomTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VisualOdomTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VisualOdomTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VisualOdomTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void VisualOdomTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(visualodom_spec);
    manager->registerFactory(profile,
                             RTC::Create<VisualOdomTest>,
                             RTC::Delete<VisualOdomTest>);
  }
  
};


