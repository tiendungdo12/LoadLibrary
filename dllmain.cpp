#include "pch.h"
#include <windows.h> // Include the Windows API header

DWORD WINAPI MyHacKLoop(LPVOID lpParam) {
	MessageBoxA(NULL, "DLL Injection successful! Choose OK to close.", "Inject Success", MB_OK);
	// Show a dialog message with no parent dialogs, content "DLL Injection successful" and OK button
	while (true) {
		Sleep(100); // Sleep for 100 milliseconds to avoid high CPU usage
		if (GetAsyncKeyState(VK_DELETE) & 0x8000) // If DELETE key is pressed
           break;
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call) // Check the reason for calling the DLL
	{
	case DLL_PROCESS_ATTACH: // When the DLL is loaded into the process
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyHacKLoop, NULL, 0, NULL); // Create a new thread to run MyHacKLoop function
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


// #include "pch.h"
// #include <windows.h>

// // --- BIẾN TOÀN CỤC ---
// // Biến để lưu "bộ não" (WndProc) GỐC của game
// WNDPROC g_pOriginalWndProc = NULL;

// // --- CẤU HÌNH ---
// const char* g_gameClassName = "ThunderRT6FormDC"; // Lớp cửa sổ (từ Spy++)
// const int g_aboutMenuID = 18;               // ID Menu (từ Spy++)


// // --- HÀM 3: "BỘ NÃO" MỚI (ĐÃ BỊ HOOK) CỦA CHÚNG TA ---
// // Đây là hàm sẽ "đứng gác" và thay thế bộ não gốc
// LRESULT CALLBACK MyHookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
// {
//     // --- LỌC THÔNG ĐIỆP ---
//     // Kiểm tra xem có phải thông điệp "click menu" không
//     if (uMsg == WM_COMMAND)
//     {
//         // Lấy ID của menu đã được click
//         int menuId = LOWORD(wParam);

//         // Kiểm tra xem có đúng là ID của "About" (212) không
//         if (menuId == g_aboutMenuID)
//         {
//             // ---- ĐÃ BẮT ĐƯỢC! ----
//             // 1. "Ăn" luôn thông điệp này. Không gửi nó cho game.
//             // 2. Hiển thị cửa sổ "About" của RIÊNG BẠN.
//             MessageBoxA(
//                 hWnd, // Cửa sổ cha là cửa sổ game
//                 "Ban da hook thanh cong!\n\n(c) 2025 by User", // Nội dung
//                 "Cua so cua toi!", // Tiêu đề
//                 MB_OK | MB_ICONINFORMATION
//             );

//             // 3. Trả về 0, báo hiệu là đã xử lý xong.
//             // Game sẽ không bao giờ biết menu "About" đã bị click.
//             return 0;
//         }
//     }

//     // --- CHUYỂN TIẾP ---
//     // Nếu đó là bất kỳ thông điệp nào khác (di chuyển chuột, ấn phím...)
//     // chúng ta phải chuyển nó cho "bộ não" GỐC xử lý.
//     // Nếu KHÔNG làm điều này, game sẽ bị "đóng băng"!!!
//     return CallWindowProc(g_pOriginalWndProc, hWnd, uMsg, wParam, lParam);
// }


// // --- HÀM 2: LUỒNG THỰC HIỆN "TRÁO NÃO" (SUBCLASSING) ---
// DWORD WINAPI HookThread(LPVOID lpParam)
// {
//     HWND hGameWnd = NULL;

//     // 1. Tìm cửa sổ game bằng Class Name
//     // Chờ cho đến khi cửa sổ game xuất hiện
//     while (hGameWnd == NULL)
//     {
//         hGameWnd = FindWindowA(g_gameClassName, NULL); // Tìm bằng Class
//         Sleep(100);
//     }

//     // 2. Lấy địa chỉ "bộ não" (WndProc) GỐC của game
//     // và LƯU NÓ LẠI vào biến toàn cục
//     g_pOriginalWndProc = (WNDPROC)GetWindowLongPtr(hGameWnd, GWLP_WNDPROC);

//     // 3. Thực hiện "TRÁO NÃO" (Subclassing)
//     // Thay thế "bộ não" GỐC bằng "bộ não" MỚI của chúng ta
//     SetWindowLongPtr(hGameWnd, GWLP_WNDPROC, (LONG_PTR)MyHookedWndProc);

//     // (Luồng này có thể kết thúc ở đây. Hook vẫn sẽ tồn tại
//     // vì chúng ta đã thay đổi con trỏ của Windows)
//     return 0;
// }


// // --- HÀM 1: DLLMAIN (CỬA NGÕ) ---
// BOOL APIENTRY DllMain(HMODULE hModule,
//     DWORD  ul_reason_for_call,
//     LPVOID lpReserved)
// {
//     switch (ul_reason_for_call)
//     {
//     case DLL_PROCESS_ATTACH:
//         // Khi DLL vừa được tiêm, tạo một luồng mới
//         // để thực hiện việc "tráo não"
//         CreateThread(NULL, 0, HookThread, NULL, 0, NULL);
//         break;
//     case DLL_THREAD_ATTACH:
//     case DLL_THREAD_DETACH:
//     case DLL_PROCESS_DETACH:
//         // (Chúng ta có thể thêm code "gỡ hook" ở đây,
//         // nhưng hiện tại không cần thiết cho bài tập này)
//         break;
//     }
//     return TRUE;
// }