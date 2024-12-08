#include "imagepickerandroid.h"
#include "qpa/qplatformnativeinterface.h"
#ifdef Q_OS_ANDROID
#include <QJniEnvironment>
#include  <QtCore/private/qandroidextras_p.h>
#endif

#include <QCoreApplication>
#include <qpa/qplatformnativeinterface.h>
#include <QGuiApplication>
#include <QFile>
#include <QString>

extern QString sStandartStoragePath;

/*Вот такой говнокод - запоминаем путь, куда сохраним сделанную фотку, что бы потом сгенерить событие её передачи в Qt приложение*/
/*PS Когда и зачем я стал передавать в кути ури вместо пути - вопрос, но 2 дня я искал, почему не копируется темповый файл*/
#ifdef Q_OS_ANDROID
 QJniObject tempImgURI;
 QJniObject tempImgAbsPath;

 extern QJniObject* pActivity;
#endif

void imagePickerAndroid::getImage()
{
 #ifdef Q_OS_ANDROID
     QJniObject ACTION_PICK = QJniObject::getStaticObjectField("android/content/Intent", "ACTION_PICK", "Ljava/lang/String;");
     QJniObject EXTERNAL_CONTENT_URI = QJniObject::getStaticObjectField("android/provider/MediaStore$Images$Media", "EXTERNAL_CONTENT_URI", "Landroid/net/Uri;");

     QJniObject intent=QJniObject("android/content/Intent", "(Ljava/lang/String;Landroid/net/Uri;)V", ACTION_PICK.object<jstring>(), EXTERNAL_CONTENT_URI.object<jobject>());

     if (ACTION_PICK.isValid() && intent.isValid())
     {
         intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("image/*").object<jstring>());

         QJniObject EXTRA_ALLOW_MULTIPLE = QJniObject::getStaticObjectField<jstring>("android/content/Intent", "EXTRA_ALLOW_MULTIPLE");
         intent.callObjectMethod("putExtra",
                                 "(Ljava/lang/String;Z)Landroid/content/Intent;",
                                 EXTRA_ALLOW_MULTIPLE.object<jstring>(),
                                 jboolean(true));

         QtAndroidPrivate::startActivity(intent.object<jobject>(), REQUEST_IMAGE_CAPTURE, this);
     }
#endif
}

 #ifdef Q_OS_ANDROID
void imagePickerAndroid::handleActivityResult(int receiverRequestCode, int resultCode, const QJniObject &data)
{

    jint RESULT_OK = QJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");
    if (receiverRequestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {

        QJniObject Uri = data.callObjectMethod("getData", "()Landroid/net/Uri;");

        if(Uri.isValid())
        {
            QString getedImage = Uri.callObjectMethod("toString", "()Ljava/lang/String;").toString();

            emit imageRecivedSignal(getedImage);
        }
        else//выбрано несколько картинок
        {
            QJniObject ClipData = data.callObjectMethod("getClipData", "()Landroid/content/ClipData;");
            int itemCount = ClipData.callMethod<jint>("getItemCount" , "()I");

            for(int iItemCounter = 0; iItemCounter < itemCount; iItemCounter++) {
                QJniObject Item = ClipData.callObjectMethod("getItemAt", "(I)Landroid/content/ClipData$Item;",iItemCounter);
                QJniObject Uri = Item.callObjectMethod("getUri", "()Landroid/net/Uri;");
                if(Uri.isValid())
                {
                    QString getedImage = Uri.callObjectMethod("toString", "()Ljava/lang/String;").toString();

                    emit imageRecivedSignal(getedImage);
                }
            }
        }


    }

    if (receiverRequestCode == REQUEST_TAKE_PHOTO && resultCode == RESULT_OK) {
        QString getedImage = tempImgAbsPath.callObjectMethod("toString", "()Ljava/lang/String;").toString();
        emit imageRecivedSignal(getedImage);
    }

}
#endif

void imagePickerAndroid::takePhoto()
{
 #ifdef Q_OS_ANDROID
        QJniObject action = QJniObject::fromString("android.media.action.IMAGE_CAPTURE");
        //Если необходимо указать Java-класс (не аргумент функции), то указывается полное имя класса (точки-разделители заменяются на "/"), например  "android/content/Intent", "java/lang/String".
        //Если аргумент функции Java-объект, то писать имя класса начиная с "L" и ";" в конце, например "Landroid/content/Intent ;", "Ljava/lang/String;".
        //Если примитивный тип или массив, то указываются соответствующие символы без разделителей, например "V" (void) или "[IIIIIII" (массив jint, и 6 jint за ним)
        //Символы, соответствия примитивны типам:
        QJniObject intent=QJniObject("android/content/Intent","(Ljava/lang/String;)V", action.object<jstring>());

        QJniObject context = QNativeInterface::QAndroidApplication::context();

        QJniObject extDir = context.callObjectMethod("getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;", NULL);

        //Абсолютный путь к каталогу для хранения файлов приложения в виде строки
        QJniObject extDirAbsPath = extDir.callObjectMethod("getAbsolutePath","()Ljava/lang/String;");
        //Добавим имя каталога для совместного использования файлов этого приложения другими приложениями. См. /res/xml/file_paths.xml
        extDirAbsPath = QJniObject::fromString(extDirAbsPath.toString() + "/shared");
        const QString extDirAbsPathStr = extDirAbsPath.toString();

        //Создать объект типа Файл для разделяемого каталога
        QJniObject sharedFolder=QJniObject("java.io.File","(Ljava/lang/String;)V",
                                                              extDirAbsPath.object<jstring>());

         const jboolean sharedFolderCreated = sharedFolder.callMethod<jboolean>("mkdirs");
         Q_UNUSED(sharedFolderCreated);

         //Прежде чем пытаться создать файл с заданным именем, нужно проверить файл с этим именем на существование
         //Предположительно путь к этому файлу

        QJniObject suggestedFilePath = QJniObject::fromString(extDirAbsPathStr+"/"+"_tmp.jpg");



        QJniObject tempImgFile=QJniObject("java.io.File","(Ljava/lang/String;)V",
                                                         suggestedFilePath.object<jstring>());
        //Удаление файла, если он существует
        if (tempImgFile.isValid()){
                const jboolean deleted = tempImgFile.callMethod<jboolean>("delete");
                Q_UNUSED(deleted);
        }

        //Создать физический файл для записи в него изображения по указанному пути
        const jboolean istempImgFileCreateNewFile = tempImgFile.callMethod<jboolean>("createNewFile");
        if(!istempImgFileCreateNewFile)
        {
            return;
        }

        //Абсолютный путь к созданному файлу в виде строки
        tempImgAbsPath = tempImgFile.callObjectMethod("getAbsolutePath","()Ljava/lang/String;");

        const QString contextFileProviderStr ("org.zlo.CarshService.fileprovider");
        const char androidFileProvider  [] = "androidx.core.content.FileProvider";



        tempImgURI = QJniObject::callStaticObjectMethod(androidFileProvider, "getUriForFile", "(Landroid/content/Context;Ljava/lang/String;Ljava/io/File;)Landroid/net/Uri;",
                                                                                     context.object<jobject>(), QJniObject::fromString(contextFileProviderStr).object<jstring>(), tempImgFile.object<jobject>());


        QJniObject MediaStore__EXTRA_OUTPUT
                = QJniObject::getStaticObjectField("android/provider/MediaStore", "EXTRA_OUTPUT", "Ljava/lang/String;");

        //Добавить URI путь файла для записи в него данных к задаче
        intent.callObjectMethod("putExtra","(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;",MediaStore__EXTRA_OUTPUT.object<jstring>(), tempImgURI.object<jobject>());

        QtAndroidPrivate::startActivity(intent, REQUEST_TAKE_PHOTO, this);
#endif
}
