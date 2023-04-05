#include "pch.h"
#include "msclr/marshal.h"
#include "msData.sdk.Wrapper.h"

using namespace msclr::interop;

namespace mstudioDatasdk {
    void Factory::GetApiVersion(int% nMajorVer,int% nMinorVer)
    {
       MStudioData::IFactoryInterface* pFactory = Factory::Get(false);
       int majorVer, minorVer;
       pFactory->GetApiVersion( majorVer, minorVer);
       nMajorVer = majorVer;
       nMinorVer = minorVer;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    String^ Factory::GetMainAppKey()
    {
        marshal_context^ context = gcnew marshal_context();
        BSTR pStrResAppKey = SysAllocString(L"");
        MStudioData::IFactoryInterface* pFactory = Factory::Get(false);
        pFactory->GetMainAppKey(&pStrResAppKey);
        String^ res= context->marshal_as<String^>(pStrResAppKey);
        ::SysFreeString(pStrResAppKey);
        delete context;
        return res;
    }

    MStudioData::IFactoryInterface* Factory::Get(bool bCheckVersion)
    {
        try
        {
            MStudioData::IFactoryInterface* pFactory = MStudioData::CMStudioDataInterface::Get(bCheckVersion);
            return pFactory;
        }
        MST_API_CATCH(L"Error loading module " + MODEL_STUDIO_DATA_MODULE_NAME);
    }
}