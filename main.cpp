#include <QCoreApplication>
#include <cusb_6xxx.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    double *get = 0;

    CUsb_6xxx *usb1=new CUsb_6xxx;
    usb1->configuration("Ultrations","Dev1","ai0",100);
    usb1->startAcquisition();
    usb1->acquerir();
    usb1->stopAcquisition();
    usb1->clearAcquisition();
    get = usb1->getDataTemps();
    printf("getData=%lf\n",get[0]);

return a.exec();
}
