#pragma once
#include "stdafx.h"
#include "CCTexture.h"
#include <list>

//��ͼ���ط�����Ϣ
struct TextureLoadQueueDataResult {
	bool success;
	int width;
	int height;
	int compoents;
	size_t size;
	BYTE* buffer;
};
//��ͼ����Ԫ����Ϣ
struct TextureLoadQueueInfo {
	CCTexture* texture;
	int x;
	int y;
	int id;
	TextureLoadQueueDataResult* pendingResult;
};

//������ͼ�ص�
typedef TextureLoadQueueDataResult*(*CCTextureLoadQueueLoadHandle)(TextureLoadQueueInfo* info, CCTexture* texture, void* data);

//��ͼ���ض���
class CCTextureLoadQueue
{
public:
	CCTextureLoadQueue();
	~CCTextureLoadQueue();

	/**
	 * ����Ҫ���ص���ͼ
	 * @param texture ��ͼʵ��
	 * @param x x����
	 * @param y y����
	 * @param id �Զ���ID
	 * @return
	 */
	CCTexture* Push(CCTexture * texture, int x, int y, int id);

	/**
	 * ������ͼ���ػص�
	 * @param handle �ص�
	 * @param data �Զ�������
	 */
	void SetLoadHandle(CCTextureLoadQueueLoadHandle handle, void *data);

	/**
	 * ���̴߳���
	 */
	void ResolveMain();
	/**
	 * ��Ⱦ�̴߳���
	 */
	void ResolveRender();

private:

	Logger*logger = nullptr;
	std::list<TextureLoadQueueInfo*> queue;
	TextureLoadQueueInfo* pendingTexture = nullptr;
	TextureLoadQueueInfo* pendingLoadDataTexture = nullptr;

	CCTextureLoadQueueLoadHandle loadHandle;
	void* loadHandleData;
};

