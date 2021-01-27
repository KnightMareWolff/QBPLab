#include "QBP_GlobalDef.h"
#include "QBP_MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImage  image("Icones/insicon.jpg");

    QPixmap pixmap = QPixmap::fromImage(image);

    QSplashScreen splash(pixmap);

    QFont *mainfont;

    mainfont = new QFont("Comic Sans MS",10, QFont::SansSerif);

    a.setFont(*mainfont);

    a.setStyleSheet("QPushButton "
                    "{ border: 2px solid #222222; "
                    "border-radius: 10px;"
                    "background-color: #9999ff;"
                    "min-width: 40px;"
                    "min-height: 20px;"
                    "}"
                    "QPushButton:pressed "
                    "{ border: 2px solid #222222; "
                    "border-radius: 10px;"
                    "background-color: #99ff99;"
                    "min-width: 40px;"
                    "min-height: 20px;"
                    "}"
                    "QToolButton "
                    "{ border: 2px solid #222222; "
                    "border-radius: 10px;"
                    "background-color: #99ff99;"
                    "}"
                    "QToolButton:pressed "
                    "{ border: 2px solid #222222; "
                    "border-radius: 10px;"
                    "background-color: #9999ff;"
                    "}"
                    "QGroupBox "
                    "{ border: 2px solid #222222; "
                    "border-radius: 10px;"
                    "background-color: #ffff99;"
                    "min-width: 40px;"
                    "min-height: 40px;"
                    "margin-top: 2ex;"
                    "}"
                    "QGroupBox:title "
                    "{ "
                    "subcontrol-origin: margin;"
                    "subcontrol-position: top center;"
                    "background-color: #ffff99;"
                    "padding: 0 10px;"
                    "}"
                    "QProgressBar "
                    "{"
                    "border: 2px solid grey;"
                    "border-radius: 5px;"
                    "text-align: center;"
                    "}"
                    "QProgressBar::chunk"
                    "{"
                    "background-color: #05B8CC;"
                    "width: 20px;"
                    "}"
                    "QMenuBar "
                    "{"
                    "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 lightgray, stop:1 darkgray);"
                    "}"
                    "QMenuBar::item "
                    "{"
                    "spacing: 3px; "
                    "padding: 1px 4px;"
                    "background: transparent;"
                    "border-radius: 4px;"
                    "}"
                    "QMenuBar::item:selected "
                    "{"
                    "background: #a8a8a8;"
                    "}"
                    "QMenuBar::item:pressed "
                    "{"
                    "background: #888888;"
                    "}"
                    "QMainWindow::separator {"
                    "    background: #888888;"
                    "    width: 10px; "
                    "    height: 10px; "
                    "}"
                    "QMainWindow::separator:hover {"
                    "    background: #a8a8a8;"
                    "}"
                    "QLineEdit {"
                    "    border: 2px solid gray;"
                    "    border-radius: 10px;"
                    "    padding: 0 8px;"
                    "    background: #99ff99;"
                    "    selection-background-color: #9999ff;"
                    "}"
                    "QComboBox {"
                    "    border: 1px solid gray;"
                    "    border-radius: 10px;"
                    "    padding: 1px 18px 1px 3px;"
                    "    min-width: 6em;"
                    "    background: #99ff99;"
                    "}"
                    "QComboBox::drop-down {"
                    "    subcontrol-origin: padding;"
                    "    subcontrol-position: top right;"
                    "    width: 15px;"
                    "    border-left-width: 3px;"
                    "    border-left-color: darkgray;"
                    "    border-left-style: solid; "
                    "    border-top-right-radius: 10px;"
                    "    border-bottom-right-radius: 10px;"
                    "}"
                    "QComboBox:on { "
                    "    padding-top: 3px;"
                    "    padding-left: 4px;"
                    "}"
                    "QComboBox::down-arrow {"
                    "    image: url(Icones/downarrow.png);"
                    "}"
                    "QComboBox::down-arrow:on {"
                    "    top: 1px;"
                    "    left: 1px;"
                    "}"
                    "QScrollBar:horizontal {"
                    "    border: 2px solid grey;"
                    "    background: #99ff99;"
                    "    height: 15px;"
                    "    margin: 0px 20px 0 20px;"
                    "}"
                    "QScrollBar::handle:horizontal {"
                    "    background: white;"
                    "    min-width: 20px;"
                    "}"
                    "QScrollBar::add-line:horizontal {"
                    "    border: 2px solid grey;"
                    "    background: #99ff99;"
                    "    width: 20px;"
                    "    subcontrol-position: right;"
                    "    subcontrol-origin: margin;"
                    "}"
                    "QScrollBar::sub-line:horizontal {"
                    "    border: 2px solid grey;"
                    "    background: #99ff99;"
                    "    width: 20px;"
                    "    subcontrol-position: left;"
                    "    subcontrol-origin: margin;"
                    "}"
                    "QScrollBar:left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
                    "    border: 2px solid grey;"
                    "    width: 3px;"
                    "    height: 3px;"
                    "    background: white;"
                    "}"
                    "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
                    "    background: none;"
                    "}"
                    "QScrollBar:vertical {"
                     "    border: 2px solid grey;"
                     "    background: #99ff99;"
                     "    width: 15px;"
                     "    margin: 22px 0 22px 0;"
                     "}"
                     "QScrollBar::handle:vertical {"
                     "    background: white;"
                     "    min-height: 20px;"
                     "}"
                     "QScrollBar::add-line:vertical {"
                     "    border: 2px solid grey;"
                     "    background: #99ff99;"
                     "    height: 20px;"
                     "    subcontrol-position: bottom;"
                     "    subcontrol-origin: margin;"
                     "}"
                     "QScrollBar::sub-line:vertical {"
                     "    border: 2px solid grey;"
                     "    background: #99ff99;"
                     "    height: 20px;"
                     "    subcontrol-position: top;"
                     "    subcontrol-origin: margin;"
                     "}"
                     "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                     "    border: 2px solid grey;"
                     "    width: 3px;"
                     "    height: 3px;"
                     "    background: white;"
                     "}"
                     "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                     "    background: none;"
                     "}"
                    );


    splash.show();

    splash.showMessage("Setting StyleSheet...");
    Sleep(1000);

    splash.showMessage("Loading modules");
    Sleep(1000);

    a.processEvents();

    splash.showMessage("Loading Main Window...");
    CQBPMainWindow *w = new CQBPMainWindow();
    //w->show();
    w->showMaximized();

    splash.finish(w);

    a.exec();

    delete w;
    w=nullptr;

    a.exit( 0 );
    return  0  ;
}
