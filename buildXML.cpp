#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>

using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filename="file.xml";

    QFile file( filename );
    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        return -1;
    }

    QDomDocument document;

    QString strHeader( "version=\"1.0\" encoding=\"UTF-8\"" );
    document.appendChild( document.createProcessingInstruction("xml", strHeader) );

    QDomElement root=document.createElement("biometric-signature-set");
    document.appendChild(root);


    QDomElement	root_elem = document.createElement( "biometric-signature" );
    root_elem.setAttribute( "name", "S0001");
    document.appendChild( root_elem );

    QDomElement item1 = document.createElement( "presentation " );
    item1.setAttribute( "name", "1" );
    item1.setAttribute( "modality", "face" );
    item1.setAttribute( "file-name", "S001-01-t10_01.jpg" );
    item1.setAttribute("file-format","jpeg");
    root_elem.appendChild( item1 );
    root.appendChild(root_elem);

   QDomElement	root_elem2 = document.createElement( "biometric-signature" );
    root_elem2.setAttribute( "name", "S0002");
    document.appendChild( root_elem2 );

    QDomElement item2 = document.createElement( "presentation " );
    item2.setAttribute( "name", "2" );
    item2.setAttribute( "modality", "face" );
    item2.setAttribute( "file-name", "S001-01-t10_01.jpg" );
    item2.setAttribute("file-format","jpeg");
    root_elem2.appendChild( item2 );
    root.appendChild(root_elem2);

    QTextStream out(&file);
    document.save( out, 4 );
    file.close();
    cout<<"it is ok now"<<endl;
    return a.exec();
}
