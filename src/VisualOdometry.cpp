//////////////////////////////////////////////////////////////////////////////
//RealSense Class
//Programed by Maika Iwai, Robot System Design Laboratory, Meijo University
//
//プログラム解説:
//このプログラムはRealSenseの起動，終了をまとめたクラスです.
//                                                                          
//依存関係:
//Intel® RealSense™ SDK
//https://github.com/IntelRealSense/librealsense
//
//バージョン情報:
//librealsense 2.28.0(2019/12/04時点)
//
//ライセンス:MIT License
//
//////////////////////////////////////////////////////////////////////////////


#include "VisualOdometry.h"

bool VisualOdometry::Init(int type)
{
  if(type == RS_T265)
    {
      //RealSenseT265の初期化
      cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
      pipe.start(cfg);
    }
  else if(type == RS_D435I)
    {
      //初期化の処理(未実装)
    }
  else
    {
      //printfで通知
      printf("Target Device is not connected");
      return false;
    }
  return true;
}

bool VisualOdometry::Close()
{
  pipe.stop();
  return true;
}

Pose3DQuaternion VisualOdometry::GetData()
{
    Pose3DQuaternion p3dq;
    
    auto frames = pipe.wait_for_frames();
    auto f = frames.first_or_default(RS2_STREAM_POSE);
    auto pose_data = f.as<rs2::pose_frame>().get_pose_data();

    p3dq.trans.x = pose_data.translation.x;
    p3dq.trans.y = pose_data.translation.y;
    p3dq.trans.z = pose_data.translation.z;
    p3dq.rot.x = pose_data.rotation.x;
    p3dq.rot.y = pose_data.rotation.y;
    p3dq.rot.z = pose_data.rotation.z;
    p3dq.rot.w = pose_data.rotation.w;
    
    return p3dq;
}

