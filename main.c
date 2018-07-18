//application that dumps a file stored in a resource.

#include <windows.h>
#define WM_APP_QUIT WM_APP+1
HWND hWnd1;
LPCSTR AppName = "TesT";
char percentOutBuf[32];
int percentage = 0;
HANDLE hT1;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void w();
void xr();
void t1();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HMENU hM, hSM, hWndList;
  POINT cursor;
  HDC hdc;
  PAINTSTRUCT ps;
  HBRUSH hOldBrush;
  RECT r;
  switch(message)
  {
    case WM_CREATE:
      CreateWindowEx(0, "STATIC", "Extracting...", WS_CHILD | WS_VISIBLE, 10, 10, 96, 20, hWnd, (HMENU)2, NULL, NULL);
      CreateWindowEx(0, "BUTTON", "Cancel", WS_CHILD | WS_VISIBLE, 140, 7, 86, 24, hWnd, (HMENU)33, NULL, NULL);
      hT1 = (HANDLE) CreateThread( NULL, 0, (PVOID) t1, 0, 0,  NULL );    
      break;
    case WM_COMMAND:
      switch(LOWORD(wParam))
      {
        case 33://Button Message
          PostQuitMessage(0);
          break;
      }
      break;
    case WM_PAINT:
      hdc = BeginPaint( hWnd, &ps );
      sprintf(percentOutBuf, "% 1d%% ", percentage );
      
      Rectangle( hdc, 24, 48, 212, 64 );
      r.left = 24;
      r.top = 48;
      r.right = percentage * .01 * (212 - r.left) + r.left;
      r.bottom = 64;
      FillRect( hdc, &r, GetSysColorBrush( COLOR_WINDOWTEXT)  );
      TextOut( hdc, 100, 48, percentOutBuf, 5);

      EndPaint( hWnd, &ps );
      break;
    case WM_APP:
      percentage = wParam;
      r.left = 25;
      r.top = 49;
      r.right = 211;
      r.bottom = 63;
      InvalidateRect( hWnd, &r, TRUE );
      break;
    case WM_DESTROY:
    case WM_APP_QUIT:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

void w()
{
  MSG msg1;
  WNDCLASS wc1;

  ZeroMemory(&wc1, sizeof wc1);
  wc1.hInstance = GetModuleHandle( NULL );
  wc1.hbrBackground = GetSysColorBrush( COLOR_BTNFACE );
  wc1.lpszClassName = AppName;
  wc1.lpfnWndProc = (WNDPROC)WndProc;
  wc1.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
  wc1.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
  wc1.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  wc1.hCursor = LoadCursor(NULL, IDC_ARROW);
  if(RegisterClass(&wc1) == FALSE) return 0;
  hWnd1 = CreateWindow(AppName, AppName, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 10, 10, 240, 120, 0, 0, wc1.hInstance, 0);
  if(hWnd1 == NULL) return 0;
  while(GetMessage(&msg1,NULL,0,0) > 0){
    TranslateMessage(&msg1);
    DispatchMessage(&msg1);
  }
  return msg1.wParam;
  
}

void xr( int id, char* file_name )
{
  HGLOBAL hgRes = NULL;
  HRSRC hrRes;
  char * res_data;
  char text_buff[255];
  DWORD res_size;
  DWORD write_amt;

  HANDLE hFile1;

  hrRes = FindResource( GetModuleHandle(NULL), MAKEINTRESOURCE( id ), RT_RCDATA );
  if( !hrRes )
  {
    MessageBox(0, "Bad Resource", 0 ,0 );
    return 0;
  }
  hgRes = LoadResource( NULL, hrRes );
  if( !hgRes )
  {
    MessageBox(0, "Not loaded.", 0, 0);
    return 1;
  }
  res_data = (char*) LockResource( hgRes );
  res_size = SizeofResource( NULL, hrRes );

  hFile1 = CreateFile( file_name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

  WriteFile( hFile1, res_data, res_size, &write_amt, NULL );
  CloseHandle( hFile1 );
  FreeResource( hgRes );

}

void t1()
{
  HGLOBAL hgResStr = NULL;
  HRSRC hrResStr;
  char* namesStr;
  int counter = 0;
  int num_files = 1;
  hrResStr = FindResource( GetModuleHandle( NULL ), MAKEINTRESOURCE( 100 ), RT_RCDATA );
  hgResStr = LoadResource( NULL, hrResStr );
  
  namesStr = strtok( hgResStr, "\n");
  num_files = atoi( namesStr );
  namesStr = strtok( NULL , "\n");
  while( namesStr != NULL )
  {
    //MessageBox(0, namesStr, 0, 0 );
    xr( 101 + counter, namesStr );
    namesStr = strtok( NULL, "\n");
    ++counter;
    PostMessage( hWnd1, WM_APP, 100.0 * counter / num_files, 0);
    Sleep(10);
  }
  int i = 0;
  //PostMessage( hWnd1, WM_APP_QUIT, 0, 0);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  w();
}
