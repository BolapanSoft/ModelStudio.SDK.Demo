#include "StdAfx.h"
#include "CppUnitTest.h"
#include <system_error>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mstudioDatasdkdemo
{
    TEST_CLASS(FactoryInterface)
    {
    public:

        TEST_METHOD(GetElement)
        {
            
        }
        //Получение главного ключа приложения из конфига
        //HRESULT GetMainAppKey(BSTR* pStrResAppKey);
        TEST_METHOD(GetMainAppKey) {
            /*MStudioData::IFactoryInterface* pFactory = MStudioData::CMStudioDataInterface::Get(false);
            Assert::IsNotNull(pFactory);
            HRESULT result=0;
            BSTR pStrResAppKey= SysAllocString(L"MainAppKey not found.");
            result = pFactory->GetMainAppKey(&pStrResAppKey);
            if (FAILED(result)) {
                const CA2W message = std::system_category().message(result).c_str();
                ::SysFreeString(pStrResAppKey);
                Assert::Fail(message);
            }
            else if (SysStringLen(pStrResAppKey) == 0) {
                ::SysFreeString(pStrResAppKey);
                Assert::Fail(L"Returns empty MainAppKey.");
            }
            std::cout << pStrResAppKey;;
            ::SysFreeString(pStrResAppKey);*/
        }
        //Получение ссылки на глобальную коллекцию определений параметров, используемую по умолчанию в ModelStudio
        //HRESULT GetGlobalParamDefs(IParamDefs** pGlobalParamDefs);
        TEST_METHOD(GetGlobalParamDefs) {
           /* MStudioData::IFactoryInterface* pFactory = MStudioData::CMStudioDataInterface::Get(false);
            Assert::IsNotNull(pFactory);
            HRESULT result = 0;
            MStudioData::IParamDefs** pGlobalParamDefs = NULL;
            result = pFactory->GetGlobalParamDefs(pGlobalParamDefs);
            if (FAILED(result)) {
                const CA2W message = std::system_category().message(result).c_str();
                Assert::Fail(message);
            }
            Assert::IsNotNull(pGlobalParamDefs);
            idx_t count;
            count = (* pGlobalParamDefs)->GetCount();
            Assert::IsTrue(count > 0);*/
        }
    };
}
