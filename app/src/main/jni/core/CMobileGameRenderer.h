#pragma once
#include "stdafx.h"
#include "COpenGLRenderer.h"
#include "CCamera.h"
#include "CCPanoramaCamera.h"
#include "CCPanoramaRenderer.h"
#include "CCTextureLoadQueue.h"
#include "CCModel.h"
#include "CCFileManager.h"
#include "CCGUInfo.h"

#include <vector>

//全景模式
enum PanoramaMode : int16_t {
	PanoramaSphere = 0,
	PanoramaCylinder,
	PanoramaAsteroid,
	PanoramaOuterBall,
	PanoramaMercator,
	PanoramaFull360,
	PanoramaFullOrginal,
	PanoramaModeMax,
};

class CMobileGameUIEventDistributor;
class CImageLoader;
class CMobileGameRenderer : public COpenGLRenderer
{
public:
	CMobileGameRenderer();
	~CMobileGameRenderer();

	void SetOpenFilePath(const char* path);
	void DoOpenFile();
	void MarkShouldOpenFile() { shouldOpenFile = true; }
	void MarkCloseFile();
	bool IsFileOpen() const;
	void MarkDestroy() override { shouldDestroy = true; }
	void SwitchMode(PanoramaMode mode);
	void SetGyroEnabled(bool enable);
	void SetEnableFullChunkLoad(bool enable);
	void SetViewCacheEnabled(bool enable) { enableViewCache = enable; }
	void SetVREnabled(bool enable);
	void SetMouseDragVelocity(float x, float y);
	void SetCachePath(char* path) { viewCachePath = path; };
	void UpdateGyroValue(float x, float y, float z, float w) const;
	void UpdateDebugValue(float x, float y, float z, float w, float u, float v);

	PanoramaMode GetMode() { return mode; }
	const char* GetImageOpenError() { return lastImageError.c_str(); }
    CCGUInfo* GetGUInfo() { return uiInfo; }
	void SetUiEventDistributor( CMobileGameUIEventDistributor*uv) { uiEventDistributor = uv; }

	float MouseSensitivityMin = 0.01f;
	float MouseSensitivityMax = 0.06f;
	float RotateSpeed = 20.0f;
	float MoveSpeed = 0.3f;
	const float MoveInGyroSensitivity = 1.0f;
	float MouseInFlatSensitivityMin = 0.01f;
	float MouseInFlatSensitivityMax = 0.06f;

	float GetMouseSensitivity();
	float GetMouseSensitivityInFlat();

private:

	Logger* logger;

	std::string currentOpenFilePath;
    std::string currentFileCachePath;

	bool ReInit() override;
	bool Init() override;
	void Render(float FrameTime) override;
	void Update() override;
	void RenderUI() override;
	void Resize(int Width, int Height) override;
	void Destroy() override;

	//全景模式
	PanoramaMode mode = PanoramaMode::PanoramaSphere;
	CCPanoramaCamera* camera = nullptr;
	CCPanoramaRenderer* renderer = nullptr;
	CCFileManager* fileManager = nullptr;
	CCTextureLoadQueue* texLoadQueue = nullptr;

	bool gyroEnabled = false;
    bool vREnabled = false;
	bool fullChunkLoadEnabled = false;

	void ShowErrorDialog();

    CMobileGameUIEventDistributor*uiEventDistributor = nullptr;
    CCGUInfo* uiInfo = nullptr;
	bool fileOpened = false;
	std::string viewCachePath;
	bool enableViewCache = true;

	std::string lastImageError;

	bool renderInitFinish = false;
	bool shouldOpenFile = false;
	bool shouldCloseFile = false;
	bool shouldDestroy = false;
	bool destroying = false;
	bool needTestImageAndSplit = false;
	float lastX = 0, lastY = 0, xoffset = 0, yoffset = 0;

	bool ShouldResetMercatorControl = false;
	bool ShouldUpdateMercatorControl = false;

	void TestSplitImageAndLoadTexture();
	void TestToLoadTextureImageCache();

    TextureLoadQueueDataResult* LoadMainTexCallback(TextureLoadQueueInfo* info, CCTexture* texture);
	TextureLoadQueueDataResult* LoadChunkTexCallback(TextureLoadQueueInfo* info, CCTexture* texture);
	static TextureLoadQueueDataResult* LoadTexCallback(TextureLoadQueueInfo* info, CCTexture* texture, void* data);
	static void FileCloseCallback(void* data);
	static void CameraFOVChanged(void* data, float fov);
	static void CameraOrthoSizeChanged(void* data, float fov);

	bool shouldSplitFullImage = true;
	bool thisFileShouldSaveCache = false;
    bool thisFileShouldLoadInCache = false;

	void ReBufferAllData();

	static void MouseCallback(COpenGLView* view, float x, float y, int button, int type);
	static void ScrollCallback(COpenGLView* view, float x, float y, int button, int type);
	void KeyMoveCallback(CCameraMovement move);

	glm::vec2 DragCurrentVelocity = glm::vec2(0);
	glm::vec2 VelocityDragLastOffest = glm::vec2(0);
	bool VelocityDragCurrentIsInSim = false;
	float VelocityDragCutSensitivity = 5.0f;
};

