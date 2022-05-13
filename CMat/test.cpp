#include "test.h"

#include "cmatvariable.h"
#include "cmatdatatype_arithmetic.h"
#include "cmatdatatype_cell.h"
#include "cmatfile.h"

//#include "cmatdatadeclare.h"

#include <iostream>
#include <windows.h>

Test::Test()
{
    LARGE_INTEGER f,c1,c2,c3,c4;
    QueryPerformanceFrequency(&f);
    double freq = f.QuadPart / 1000.0;

    CMatVariable<mxDOUBLE_CLASS,true> v("v",{1,1});


    CMatVariable<mxDOUBLE_CLASS,false> vv("vv",{2,2});

    CMatVariable<mxCELL_CLASS,false> vvv("vvv",{10,1});
//    CMatVariable<mxCELL_CLASS,true> vvvv({4});


    CMatDataType_Double<true> p = v[0];
    auto pp = vv[0];
    CMatDataType_Cell ppp = vvv[0];
//    auto &pppp = vvvv[0];
//    double t = p->Real<double>();
    p.Real() = 1;
    p.Imaginary() = 2;

//    double &data = vvv.At({3,1}).At<mxDOUBLE_CLASS>({3});
    ppp.Retype(mxDOUBLE_CLASS,false);
    ppp.Resize({2});

    double d;
//    d = ppp.DataAt<mxDOUBLE_CLASS>({0}) = 1;
//    ppp.DataAt<mxINT64_CLASS>({1,1}) = 2;
//    ppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0}).At<mxDOUBLE_CLASS,true>({0}).Real() = 1;


//    ppp.At<mxCELL_CLASS>({0});

    CMatDataType_Cell a = ppp.At<mxCELL_CLASS>({0});
    a.Retype(mxCELL_CLASS);
    ppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0});
    ppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0});
    ppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0}).At<mxDOUBLE_CLASS,true>({0}).Real() = 1;
    ppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0}).At<mxDOUBLE_CLASS,true>({0}).Imaginary() = 1;

//    pppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0}).At<mxDOUBLE_CLASS,false>({0}).Real() = 1;
//    pppp.At<mxCELL_CLASS>({0}).At<mxCELL_CLASS>({0}).At<mxDOUBLE_CLASS,false>({0}).Imaginary() = 1;

    QueryPerformanceCounter(&c1);
    vvv.Resize({10,1});
    for(mwSize i = 0;i < 10;++i)
    {
        CMatDataType_Cell cell = vvv.At({i,0});
        cell.Retype(mxDOUBLE_CLASS,true,{181,23,301});
//        cell.Retype(mxDOUBLE_CLASS,true,{10,10});
//        cell.Resize({10,10});
//        cell.At<mxDOUBLE_CLASS,false>({181,23,301});


//        const std::vector<mwSize>& dims = cell.Dims();
        for(mwSize j = 0;j < cell.Size();++j)
        {
//            CMatDataType_Double_Base *p = cell[i];
//            CMatDataType_Double<true> *p = dynamic_cast<CMatDataType_Double<true> *>(cell[i]);
            CMatDataType_Double<true> doubleData = cell[j];
//            cell<mxDOUBLE_CLASS,true>[i];
//            cell.operator[]<mxDOUBLE_CLASS,true>[i];


            doubleData.Real() = j * 1.0;
            doubleData.Imaginary() = j * 2.0;

//            double &R = doubleData.Real();
//            double &I = doubleData.Imaginary();

//            R = 10;
//            I = 20;
        }

//        mwSize c = 0;
//        for(mwSize j = 0;j < 181;++j)
//        {
//            for(mwSize k = 0;k < 23;++k)
//            {
//                for(mwSize l = 0;l < 301;++l)
//                {
//                    ++c;
//                    CMatDataType_Double<true> doubleData;
//                    cell.At({j,k,l},doubleData);

//                    doubleData.Real() = c * 1.0;
//                    doubleData.Imaginary() = c * 2.0;
//                }
//            }
//        }
    }

//    std::vector<std::vector<mwSize> > t(10);
//    for(mwSize i = 0;i < 10;++i)
//    {
//        std::vector<mwSize> tt(vvv.At({0,0}).Size());
//        t[i] = tt;
//    }

    QueryPerformanceCounter(&c2);

//    for(mwSize i = 0;i < 10;++i)
//    {
//        std::vector<mwSize> &tt = t[i];
//        for(mwSize j = 0;j < tt.size();++j)
//        {

//            double R = tt[j];
////            double I = doubleData.Imaginary();

//            int a = R;
//        }
//    }

    for(mwSize i = 0;i < 10;++i)
    {
        CMatDataType_Cell cell = vvv.At({i,0});
        for(mwSize j = 0;j < cell.Size();++j)
        {
            CMatDataType_Double<true> doubleData = cell[j];


            double R = doubleData.Real();
            double I = doubleData.Imaginary();

            int a = R = I;
        }
    }
    QueryPerformanceCounter(&c3);

//    CMatVariable<mxCELL_CLASS,false> vvvvv("vvvvv");
//    vvvvv.Resize({1,5});

    CMatFile matFile("write.mat","w");
    matFile.Write(vvv);
//    matFile.Write(vvvvv);
    matFile.Close();
    QueryPerformanceCounter(&c4);

    std::cout
            << "create and set complex double data[{181,23,301}]x10:" << (c2.QuadPart - c1.QuadPart) / freq << std::endl
            << "read complex double data[{181,23,301}]x10:" << (c3.QuadPart - c2.QuadPart) / freq << std::endl
            << "save complex double data[{181,23,301}]x10:" << (c4.QuadPart - c3.QuadPart) / freq << std::endl;

    CMatFile matFile1("write.mat","r");

    while(CMatDataBase* vvvv = matFile1.ReadNext())
    {
        delete vvvv;
    }


    CMatVariable<mxSINGLE_CLASS,true> vvvvvv("v",{1,1});

//    std::cout << p.TypeString() << /*pp.TypeString() << */ppp.TypeString()/* << pppp.TypeString()*/;
}
