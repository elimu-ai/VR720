#pragma once
#ifndef VR720_CCMODEL_H
#define VR720_CCMODEL_H
#include "stdafx.h"

class CCMaterial;
class CCMesh;
//ģ����
class CCModel
{
public:
	CCModel();
	~CCModel();

	//��ȡģ�ͱ任����
	glm::mat4 GetModelMatrix();

	/**
	 * ˢ������
	 */
	virtual void UpdateVectors();
	/**
	 * ����ģ��λ�ú���ת
	 */
	virtual void Reset();
	/**
	 * ����ģ��
	 */
	void Render() const;
	/**
	 * ���»�������
	 */
	void ReBufferData() const;

	//ģ���Ƿ�ɼ�
	bool Visible = true;

	//ģ��λ��
	glm::vec3 Position = glm::vec3(0.0f);
	//���ű���
	glm::vec3 LocalScale = glm::vec3(1.0f);


	//ģ�Ͳ���
	CCSmartPtr<CCMaterial> Material;
	//ģ������
	CCSmartPtr<CCMesh> Mesh;

	const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 WorldFront = glm::vec3(0.0f, 0.0f, 1.0f);
	const glm::vec3 WorldRight = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 GetFront() ;
	glm::vec3 GetUp() ;
	glm::vec3 GetRight() ;

	/**
	 * ����λ��
	 * @param position �����λ��
	 */
	void SetPosition(glm::vec3 position);
	void SetLocalEulerAngles(glm::vec3 eulerAngles);
	void SetEulerAngles(glm::vec3 eulerAngles);
	void SetLocalRotation(glm::quat rotation);
	void SetRotation(glm::quat rotation);

	glm::vec3 GetLocalEulerAngles() const;
	glm::vec3 GetEulerAngles() const;
	glm::quat GetLocalRotation() const;
	glm::quat GetRotation() const;

	bool VectorDirty = true;

protected:

	glm::vec3 mEulerAngles = glm::vec3(0,0,0);
	glm::vec3 mLocalEulerAngles = glm::vec3(0,0,0);
	glm::quat mLocalRotation = glm::quat();
	glm::quat mRotation = glm::quat();

	glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 mFront = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 mRight = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 mLocalUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 mLocalFront = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 mLocalRight = glm::vec3(0.0f, 0.0f, 1.0f);
};

#endif

