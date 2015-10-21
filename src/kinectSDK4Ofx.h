#pragma once
#include "ofMain.h"
#include <Kinect.h>



class kinectSDK4Ofx{
  public:
	  kinectSDK4Ofx();
	  bool Open();

	  void init();
	  void init(bool depth, bool color);

	  void Update();
	  void drawDepth(int x, int y, int w, int h);
	  void drawColor(int x, int y, int w, int h);
	  void getDepthFrameBuffer(int w, int h, int* buffer);

	  void setMaxRange(int range);
	  void setMinRange(int range);
	  /// static kinect depth size
	  const static int depthWidth = 512;
	  const static int depthHeight = 424;
	  const static int colorWidth = 1920;
	  const static int colorHeight = 1080;
  private:
	  IKinectSensor* m_pKinectSensor; // Current Kinect
	  IColorFrameReader* m_pColorFrameReader; // Color reader
	  IDepthFrameReader* m_pDepthFrameReader; //Depth reader

	  ofImage color; // oF用カラーイメージ
	  ofImage depth; // oF用デプスイメージ
	  UINT16 depthBuffar[depthWidth*depthHeight]; // int参照用デプスバッファ
	  bool depthFlag;
	  bool colorFlag;
	  int maxRange, minRange;
};

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
    if (pInterfaceToRelease != NULL)
    {
        pInterfaceToRelease->Release();
        pInterfaceToRelease = NULL;
    }
}