#ifndef __TestClass_H
#define __TestClass_H

#define IS_BINDEABLE

#include <vector>

namespace Test
{
    class CTestClass : public CBase, private CPriv
    {
        public:
            CTestClass();
            CTestClass(int);
            ~CTestClass();
            
            void method_public_1();
            int method_public_2();
            float method_public_3(float);
            float3 method_public_4(float,float,float);
            std::vector<float> method_public_5(float,float,float);
        private:
            void method_private_1();
            int method_private_2();
            float method_private_3(float);
            float3 method_private_4(float,float,float); 
    }
}

#endif //__TestClass_H