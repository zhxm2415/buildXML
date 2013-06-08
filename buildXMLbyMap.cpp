#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>
#include <QDir>

using namespace std;
QMap<QString,int>file_info;

bool travel_dir(char * dir_path)
{
  QDir dir(dir_path);
  if(!dir.exists())
  {
      cerr<<"the dir"<<dir_path<<" does not exist"<<endl;
      return false;
  }

  dir.setFilter(QDir::Files);  //滤出文件，使读出的名字没有目录名，只包含文件名
  QStringList picFiles = dir.entryList();  //读出文件名放到链表中；

   // print the file name into a txt file
  QFile file_name("filename.txt");
  if(!file_name.open(QIODevice::WriteOnly))
  {
      std::cerr<<"Cannot open filename.txt file for writing:"
              <<qPrintable(file_name.errorString()) << std::endl;
      return false;
  }
   QTextStream out_name(&file_name);

 for(int i = 0;i < picFiles.length(); i++)//打印出文件名
 {
        out_name<< picFiles.at(i)<<" "<<i+1<<endl;
        file_info.insert(picFiles.at(i),i+1);
 }
 file_name.close();
 return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filename="file.xml";

    QFile file( filename );
    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        return -1;
    }

    travel_dir("/home/zbliu/openbr_test/cas_effective/");

    QDomDocument document;

    QString strHeader( "version=\"1.0\" encoding=\"UTF-8\"" );
    document.appendChild( document.createProcessingInstruction("xml", strHeader) );

    QDomElement root=document.createElement("biometric-signature-set");
    document.appendChild(root);

    QMap<QString,int>::iterator it; //遍历map

    for ( it = file_info.begin(); it != file_info.end(); ++it ) {
         QString str=it.key();
         QString str_prefix=str.mid(0,9);
         //QString modify_name=str_prefix.mid(0,1)+"0"+str_prefix.mid(1,3);

    QDomElement  root_elem_temp = document.createElement( "biometric-signature" );
    root_elem_temp.setAttribute( "name", str_prefix);
    document.appendChild( root_elem_temp );

    QDomElement item = document.createElement( "presentation " );
    item.setAttribute( "name", QString::number(it.value(),10));
    item.setAttribute( "modality", "face" );
    item.setAttribute( "file-name", it.key() );
    item.setAttribute("file-format","jpeg");
    root_elem_temp.appendChild( item );
    root.appendChild(root_elem_temp);
    }

    QTextStream out(&file);
    document.save( out, 4 );
    file.close();
    cout<<"it is ok now"<<endl;
    return a.exec();
}
