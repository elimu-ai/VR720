#pragma once
#ifndef STRING_HLP_H
#define STRING_HLP_H
#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string>  
#include <vector>

//�ַ���������
class CStringHlp
{
public:

	/**
	 * ��ȡ��С�Ŀɶ��ַ���
	 * @param byteSize ��С
	 * @return
	 */
	static std::string GetFileSizeStringAuto(long long byteSize);

	static std::string & FormatString(std::string & _str, const char * format, ...);
	static std::wstring & FormatString(std::wstring & _str, const wchar_t * format, ...);
	static std::wstring FormatString(const wchar_t * format, ...);
	static std::wstring FormatString(const wchar_t *format, va_list marker);
	static std::string FormatString(const char * format, va_list marker);
	static std::string FormatString(const char * format, ...);

	/**
	 * ���ַ� Unicode ת Char
	 * @param szStr Դ�ַ���
	 * @return
	 */
	static std::string UnicodeToAnsi(std::wstring szStr);
	/**
	 * ���ַ� Unicode ת UTF8
	 * @param unicode Դ�ַ���
	 * @return
	 */
	static std::string UnicodeToUtf8(std::wstring unicode);
	/**
	 * Char ת���ַ� Unicode
	 * @param szStr Դ�ַ���
	 * @return
	 */
	static std::wstring AnsiToUnicode(std::string szStr);
	/**
	 * UTF8 �ַ���ת Unicode���ַ�
	 * @param szU8 Դ�ַ���
	 * @return
	 */
	static std::wstring Utf8ToUnicode(std::string szU8);

#ifdef VR720_ANDROID

	static jstring charTojstring(JNIEnv* env, const char* pat);
	static char* jstringToChar(JNIEnv* env, jstring jstr);

#endif
};

#endif








