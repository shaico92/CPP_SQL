#include "Language.h"

 void Language::castToUnicode(char ptr[], wstring str,size_t size) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8String = converter.to_bytes(str);

    // Convert UTF-8 string to char*

    int iz = 0;
    for (size_t i = 0; i < size &&i< utf8String.length(); i++)
    {

        ptr[i] = utf8String[i];
        iz = i;
    }
    if (ptr[iz] < 0 && ptr[iz - 1] > 0)
    {
        ptr[iz] = '\0';
       
    }
    memset(ptr+iz+1,0, size-iz);

    

}
