//#include "mainwindow.h"

//#include <QApplication>
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
