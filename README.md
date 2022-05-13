# CMat
A matlab file and variable interface written in moden c++ depend on matlab api

Depency：
  Include:
    Add matlab include dir(which dir contain mat.h) to your project include dirs

  DLL:
    Add matlab lib dir(which dir contain libmat.lib/libmx.lib) to your projcec lib paths,add libmat.lib/libmx.lib to your import dll list

Code Sample:
//Step1: Create A {181,23,301} Complex Double matrix * 10 into a cell named "vvv":

  #include "cmat/cmatvariable.h" //or
  #include "cmat/cmatfile.h"
  
  CMatVariable<mxCELL_CLASS,false> vvv("vvv",{10,1});                                         //create a variable named "vvv" which contain 10*1 cell 
  for(mwSize i = 0;i < vvv.Dims()[0];++i)
  {
      CMatDataType_Cell cell = vvv.At({i,0});
      cell.Retype(mxDOUBLE_CLASS,true,{181,23,301});                                          //retype every cell to complex double {181,23,301}

        for(mwSize j = 0;j < cell.Size();++j)
        {
            CMatDataType_Double<true> doubleData = cell[j];

            doubleData.Real() = j * 1.0;                                                      //fill some value to matrix
            doubleData.Imaginary() = j * 2.0;
        }
  }
  
//Step2:Write the "vvv" variable to mat file "write.mat"
  CMatFile matFileWrite("write.mat","w");
  matFile.Write(vvv);
  matFile.Close();
  
  
//Step3:Read the "write.mat"
  CMatFile matFileRead("write.mat","r");
  while(CMatDataBase* vvvv = matFile1.ReadNext())                                             //read next variable till the end
                                                                                              // or CMatDataBase* vvvv = matFile1.Read("vvv") to read a specific variable named "vvv"
  {
      mxClassID classID = vvvv->Type();
      const std::vector<mwSize> &dims = vvvv->Dims();

      switch(classID)
      {
      case mxCELL_CLASS:
      {
          CMatData<mxCELL_CLASS,false> &p = dynamic_cast<CMatData<mxCELL_CLASS,false> &>(*vvvv);
          for(mwSize i = 0;i < p.Size();++i)
          {
              assert(p[i].Type() == mxDOUBLE_CLASS && p[i].IsComplex());

              CMatDataType_Double<true> doubleData = p[i].At({0,0,0});                        //read first complex double,index start from 0

              double real = doubleData.Real();
              double imag = doubleData.Imaginary();

              doubleData = p[i].At({180,22,300});                                             //read last when dims is {181,23,301} and last index is {180,22,300}
              double realLast = doubleData.Real();
              double imagLast = doubleData.Imaginary();
          }
      }break;
          //case mxDOUBLE_CLASS ...{}break;
      default:
          break;
      }
      delete vvvv;                                                                        //delete the variable pointer
  }

Test(put these code on main.c):  
  #include <iostream>
  #include "mat.h"


  //#include "C:\\Program Files (x86)\\Visual Leak Detector\\include\\vld.h"

  #include "CMat/test.h"
  #include "CMat/cmatdata.h"
  #include "CMat/cmatexception.h"
  int main(int argc, char *argv[])
  {
  //    QApplication a(argc, argv);
      try {
          Test *test = new Test();
          delete test;
      }  catch (CMatException_OpenMatFileFailed &e) {
          //
          std::cout << "exception:" << e.what() << std::endl;
      }catch(CMatException &e){
          std::cout << "exception:" << e.what() << std::endl;
      }




  //    return a.exec();
  }
  
Test Result( qt(mingw8.1.0) on windows10（cpu:4900h,debug model）):
create and set complex double data[{181,23,301}]x10: 3379.98 (ms)
read complex double data[{181,23,301}]x10: 3129.36 (ms)
save complex double data[{181,23,301}]x10: 12031.8 (ms)
load complex double data[{181,23,301}]x10: 1531.44 (ms)
