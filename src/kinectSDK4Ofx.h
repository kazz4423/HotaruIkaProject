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

	  ofImage color; // oF�p�J���[�C���[�W
	  ofImage depth; // oF�p�f�v�X�C���[�W
	  UINT16 depthBuffar[depthWidth*depthHeight]; // int�Q�Ɨp�f�v�X�o�b�t�@
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