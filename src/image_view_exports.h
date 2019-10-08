#ifndef IMAGE_VIEW_EXPORTS_H
#define IMAGE_VIEW_EXPORTS_H

#if defined(_WIN32) || defined(_WIN64) || defined(WINCE) || defined(__MINGW32__)
#ifdef IMAGE_VIEW
#define IMAGE_VIEW_EXPORT __declspec(dllexport)
#else
#define IMAGE_VIEW_EXPORT __declspec(dllimport)
#endif
#else
#define IMAGE_VIEW_EXPORT
#endif

#endif  // IMAGE_VIEW_EXPORTS_H
