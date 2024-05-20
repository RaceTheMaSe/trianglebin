#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windowsx.h>
#undef GetWindowFont // because imgui
#include <shellscalingapi.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <string>

using Microsoft::WRL::ComPtr;

std::wstring WideFromMultiByte(const char* s);
std::wstring WideFromMultiByte(const std::string& s);
std::string MultiByteFromWide(const wchar_t* s);
std::string MultiByteFromWide(const std::wstring& s);

std::string MultiByteFromHR(HRESULT hr);

void SimpleMessageBox_FatalError(const char* fmt, ...);

bool detail_CheckHR(HRESULT hr, const char* file, const char* function, int line);
bool detail_CheckWin32(BOOL okay, const char* file, const char* function, int line);

#if defined(_MSC_VER)
#define CHECKHR(hr) detail_CheckHR(hr, __FILE__, __FUNCSIG__, __LINE__)
#define CHECKWIN32(okay)                                                       \
  detail_CheckWin32(okay, __FILE__, __FUNCSIG__, __LINE__)
#else
  #define CHECKHR(hr) detail_CheckHR(hr, __FILE__, __FUNCTION__, __LINE__)
  #define CHECKWIN32(okay) \
  detail_CheckWin32(okay, __FILE__, __FUNCTION__, __LINE__)
#endif
