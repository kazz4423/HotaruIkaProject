#include "kinectSDK4Ofx.h"

kinectSDK4Ofx::kinectSDK4Ofx(){
}

bool kinectSDK4Ofx::Open(){
	HRESULT hr = GetDefaultKinectSensor(&m_pKinectSensor);
	// ����kinect������������
	if(m_pKinectSensor){
		hr = m_pKinectSensor->Open(); // kinect�N��

		if(depthFlag){
			IDepthFrameSource* pDepthFrameSource = NULL;
			if(SUCCEEDED(hr)){
				hr = m_pKinectSensor->get_DepthFrameSource(&pDepthFrameSource);
			}
			if(SUCCEEDED(hr)){
				hr = pDepthFrameSource->OpenReader(&m_pDepthFrameReader);
			}
			SafeRelease(pDepthFrameSource);
		}
		if(colorFlag){
			IColorFrameSource* pColorFrameSource = NULL;
			if(SUCCEEDED(hr)){
				hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
			}
			if(SUCCEEDED(hr)){
				hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
			}
			SafeRelease(pColorFrameSource);
		}
	}
	// ����kinect��������Ȃ��B�N���ł��Ȃ��ꍇ��
	if(!m_pKinectSensor ||FAILED(hr)){
		std::cout << "no kinect sensor found!" << std::endl;
	}

	depth.allocate(depthWidth, depthHeight, OF_IMAGE_COLOR_ALPHA);
	color.allocate(colorWidth, colorHeight,OF_IMAGE_COLOR_ALPHA);

	return SUCCEEDED(hr);
}

void kinectSDK4Ofx::init(){
	depthFlag =true; 
	colorFlag = false;


}

void kinectSDK4Ofx::init(bool depth, bool color){
	depthFlag = depth;
	depthFlag = color;
	minRange = 500;
	maxRange = 8000;
}

void kinectSDK4Ofx::Update(){
	if(!m_pDepthFrameReader){
		return;
	}

	if(depthFlag){
		IDepthFrame* pDepthFrame = NULL;
		HRESULT hr = m_pDepthFrameReader->AcquireLatestFrame(&pDepthFrame); // �ŐV�̃J���[�t���[�����擾����
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 512;
		int nHeight = 384;
		USHORT nDepthMinReliableDistance = 0;
		USHORT nDepthMaxDistance = 0;
		UINT nBufferSize = 0;
		UINT16 *pBuffer = NULL;

		if(SUCCEEDED(hr)){
			hr = pDepthFrame->get_FrameDescription(&pFrameDescription); // DepthFrame���炻�̃t���[���̏��𓾂�B
		}
		if(SUCCEEDED(hr)){
			//hr = pFrameDescription->get_Width(&nWidth);
		}
		if(SUCCEEDED(hr)){
			//hr = pFrameDescription->get_Height(&nHeight);
		}
		if(SUCCEEDED(hr)){
			// �f�v�X���̃t�������W���݂邽��(�M�p�ł��Ȃ������̐[�������܂�)
			// nDepthMaxDistance�����E�̐[����臒l�ɐݒ肷��B
			nDepthMaxDistance = USHRT_MAX;
			// Note: �����M�p�ł���˒��Ńt�B���^�����O�������ꍇ�́A�ȉ��̃R�����g�A�E�g���O���Ă��������B
			 //// hr = pDepthFrame->get_DepthMaxReliableDistance(&nDepthMaxDistance);
		}
		if(SUCCEEDED(hr)){
			hr = pDepthFrame->AccessUnderlyingBuffer(&nBufferSize,&pBuffer); // Frame����Depth�f�[�^���i�[���ꂽ�z��̃|�C���^���擾����(UINT16�^)�B
		}
		if(SUCCEEDED(hr)){
			//depthBuffar = pBuffer; // int�^�̃o�b�t�@�ɗ�������
		}
		if(SUCCEEDED(hr)){
			BYTE* data = depth.getPixels();
			const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);
			int i = 0;
			while(pBuffer < pBufferEnd)
			{
				USHORT depth = *pBuffer;
				depthBuffar[i] = depth;
				BYTE intensity = static_cast<BYTE>((depth >= minRange) && (depth <= maxRange) ? (256-(depth-500)/(1500/256)) : 0);
				*data = intensity;
				*(data+1) = intensity;
				*(data+2) = intensity;
				data = data+4; //�����C��������
				++pBuffer;
				i++;
			}
			depth.update();
		}
		SafeRelease(pDepthFrame);
	}

	if(colorFlag){
		IColorFrame* pColorFrame = NULL;
		HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		ColorImageFormat imageFormat = ColorImageFormat_None;
		UINT nBufferSize = 0;
		BYTE *data = color.getPixels();

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if(SUCCEEDED(hr)){
			nBufferSize = colorWidth * colorHeight * 4;
			hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, data, ColorImageFormat_Rgba);
		}
		if(SUCCEEDED(hr)){
			color.update();
		}
		SafeRelease(pColorFrame);
	}
}

void kinectSDK4Ofx::drawDepth(int x, int y, int w, int h){
	depth.draw(x,y,w,h);
}

void kinectSDK4Ofx::drawColor(int x, int y, int w, int h){
	color.draw(x,y,w,h);
}

//�C�Ӊ𑜓x�ŃN���b�s���O����depth�o�b�t�@
void kinectSDK4Ofx::getDepthFrameBuffer(int w, int h, int* buffer){
	if(depthBuffar != NULL){
		if(w <= depthWidth && h <= depthHeight){
			int* pDepthBuffer = new int[w*h];
				for(int y = 0; y < h;y++){
					for(int x = 0; x < w;x++){
						buffer[w*y + x] = (int)depthBuffar[w*y + (w-1-x)];
					}
				}
				//buffer = pDepthBuffer;
			delete [
			] pDepthBuffer;
		}
	}
}

void kinectSDK4Ofx::setMaxRange(int range){
	maxRange = range;
}

void kinectSDK4Ofx::setMinRange(int range){
	minRange = range;
}