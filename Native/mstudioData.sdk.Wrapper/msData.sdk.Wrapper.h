#pragma once
#include "CSDataInterfaces.h"

using namespace System;
using namespace MStudioData;

namespace mstudioDatasdk {
	public ref class Factory
	{
		
    public:
        void GetApiVersion([Runtime::InteropServices::Out] int% nMajorVer, [Runtime::InteropServices::Out] int% nMinorVer);
        String ^GetMainAppKey();
        void GetGlobalParamDefs() {
            MStudioData::IFactoryInterface* pFactory = MStudioData::CMStudioDataInterface::Get(false);
            if (!pFactory) {
                //TODO: Throw assembly not found exception
            }
            HRESULT result = 0;
            MStudioData::IParamDefs** pGlobalParamDefs = NULL;
            result = pFactory->GetGlobalParamDefs(pGlobalParamDefs);
            if (FAILED(result)) {
                //TODO: Throw error operation
            }

       }
    private:
        //Значение кэшируется внутри вызываемого клиентского модуля msData
        static IFactoryInterface* Get(bool bCheckVersion);
	};
}
