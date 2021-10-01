#pragma once
#include<wrl.h>
#include<iostream>



namespace Utils {

    
    inline void ThrowIfFailed(HRESULT hr, std::exception e) {
        if (FAILED(hr))
            throw e.what();
    }


}