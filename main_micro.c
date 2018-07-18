//application that dumps a file stored in a resource.

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  HGLOBAL hgRes = NULL;
  HRSRC hrRes;
  char * res_data;
  char text_buff[255];
  DWORD res_size;
  DWORD write_amt;

  HANDLE hFile1;

  hrRes = FindResource( hInst, MAKEINTRESOURCE( 101 ), RT_RCDATA );
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

  hFile1 = CreateFile( "file.exe", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

  WriteFile( hFile1, res_data, res_size, &write_amt, NULL );
  CloseHandle( hFile1 );
  FreeResource( hgRes );
}
