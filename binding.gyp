{
  "targets": [
    {
      "target_name": "addon",      
      "sources": [
        "c++/addon.cpp",
        "c++/classes_wrap/usbdevWrap.cpp",
        "c++/classes/usbdev.cpp",
        "c++/classes/moc/moc_usbdev.cpp",
        "c++/classes_wrap/videostreamingWrap.cpp",
        "c++/classes/videostreaming.cpp",
        "c++/classes/moc/moc_videostreaming.cpp",
        "c++/classes/cameraviewer.cpp",
        "c++/classes/moc/moc_cameraviewer.cpp",
        "c++/classes/otracker.cpp",
        "c++/classes_signals/utilsprocess.cpp",
        "c++/classes_signals/qutils.cpp",
        "c++/classes_signals/oscann_interface.cpp",
        "c++/classes_signals/oscann_adaptor.cpp",
        "c++/classes_signals/moc/moc_oscann_adaptor.cpp",
        "c++/classes_signals/moc/moc_oscann_interface.cpp",
        "c++/classes_signals/moc/moc_qutils.cpp"
      ],
      "include_dirs": [
        "c++",
        "c++/classes",
        "c++/classes/moc",
        "c++/classes_signals",
        "c++/classes_signals/moc",
        "c++/classes_wrap",
        "/usr/include/x86_64-linux-gnu/qt5",
        "/usr/include/x86_64-linux-gnu/qt5/QtCore",
        "/usr/include/x86_64-linux-gnu/qt5/QtWidgets",
        "/usr/include/x86_64-linux-gnu/qt5/QtGui",
        "/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport",
        "/usr/include/x86_64-linux-gnu/qt5/QtQuick",
        "/usr/include/x86_64-linux-gnu/qt5/QtSql",
        "/usr/include/x86_64-linux-gnu/qt5/QtDBus",
        "/usr/include/x86_64-linux-gnu/qt5/QtQml",
        "/usr/include/x86_64-linux-gnu/qt5/QtNetwork",
        #"/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64",
        "/usr/local/include/node",
        "/usr/include/python3.8",
        "/usr/local/include/opencv4",
        "/usr/local/include/bsoncxx/v_noabi",
        "/usr/local/include/mongocxx/v_noabi",
        "/usr/local/include",
        "/usr/include",
      ],
      'conditions': [
        ['OS=="linux"', {
          'library_dirs': [
            '/usr/lib/x86_64-linux-gnu',
            '/usr/X11R6/lib64',
            '/usr/local/lib',
            '/lib',
            '/usr/libx86_64-linux-gnu',
            #'/opt/Qt5.14.2/5.14.2/gcc_64/lib', #importante el orden, si se pone primera da el error de Qt_5 not defined
          ],
          'cflags_cc!': [
            '-fno-rtti',
          ],
          'cflags_cc+': [
            '-frtti',
            '-fexceptions'
          ],
          #'cflags!': [
          #],
          'cflags': [
            '<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Network Qt5Qml Qt5DBus Qt5Sql Qt5Quick Qt5Widgets Qt5PrintSupport)'
          ],
          'ldflags': [
            '<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Network Qt5Qml Qt5DBus Qt5Sql Qt5Quick Qt5Widgets Qt5PrintSupport)'
          ],
          'libraries': [
            '<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Network Qt5Qml Qt5DBus Qt5Sql Qt5Quick Qt5Widgets Qt5PrintSupport)',
            #'-lQt5QmlModels',
            '-lv4lconvert',
            '-lavutil',
            '-lavcodec',
            '-lavformat',
            '-lswscale',
            '-ludev',
            '-lopencv_core',
            '-lopencv_highgui',
            '-lopencv_imgproc',
            '-lopencv_videoio',
            '-lopencv_imgcodecs',
            '-lrt', 
            '-lmongocxx',
            '-lbsoncxx',
            '-ltbb',
            '-lboost_system',
            '-lGL',
            '-lpthread',
          ],
          'defines': [
            'OSCANN=1'
          #  'QT_NO_DEBUG',
          #  'QT_PRINTSUPPORT_LIB',
          #  'QT_WIDGETS_LIB',
          #  'QT_QUICK_LIB',
          #  'QT_GUI_LIB',
          #  'QT_SQL_LIB',
          #  'QT_DBUS_LIB',
          #  'QT_QML_LIB',
          #  'QT_NETWORK_LIB',
          #  'QT_CORE_LIB'
          ],
        }]
      ]
    }
  ]
}

#'cflags': [
#    '<!@(pkg-config --cflags Qt5QmlModels QtGui QtXml QtSql QtCore QtDBus Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets Qt5Quick Qt5Qml Qt5Sql Qt5Svg Qt5Xml Qt5DBus Qt5Help Qt5OpenGL Qt5Script Qt5WebKit Qt5XcbQpa Qt5CLucene Qt5Network Qt5Designer Qt5UiTools QtCLucene QtNetwork Qt5QuickTest Qt5X11Extras QtScript Qt5Concurrent Qt5FeedBack Qt5QmlDevTools QtOrganizer Qt5ScriptTools Qt5XmlPatterns Qt5PrintSupport Qt5QuickWidgets QtDeclarative QtXmlPatterns Qt5Organizer Qt5Positioning Qt5WebKitWidgets Qt5PlatformSupport Qt5QuickParticles Qt5OpenGLExtensions Qt5MultimediaQuick_p Qt5MultimediaWidgets Qt5DesignerComponents Qt5EglDeviceIntegration qtga qtiff qtwcodecs qtscriptdbus qtfeedback_mmk qtquick2plugin qtuiotouchplugin qtorganizer_memory qtaccesiblewidgets qtracegraphicssystem qtquickcontrolsplugin qtquickextrasflatplugin)'
#],
#'ldflags': [
#    '<!@(pkg-config --libs-only-L --libs-only-other Qt5QmlModels QtGui QtXml QtSql QtCore QtDBus Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets Qt5Quick Qt5Qml Qt5Sql Qt5Svg Qt5Xml Qt5DBus Qt5Help Qt5OpenGL Qt5Script Qt5WebKit Qt5XcbQpa Qt5CLucene Qt5Network Qt5Designer Qt5UiTools QtCLucene QtNetwork Qt5QuickTest Qt5X11Extras QtScript Qt5Concurrent Qt5FeedBack Qt5QmlDevTools QtOrganizer Qt5ScriptTools Qt5XmlPatterns Qt5PrintSupport Qt5QuickWidgets QtDeclarative QtXmlPatterns Qt5Organizer Qt5Positioning Qt5WebKitWidgets Qt5PlatformSupport Qt5QuickParticles Qt5OpenGLExtensions Qt5MultimediaQuick_p Qt5MultimediaWidgets Qt5DesignerComponents Qt5EglDeviceIntegration qtga qtiff qtwcodecs qtscriptdbus qtfeedback_mmk qtquick2plugin qtuiotouchplugin qtorganizer_memory qtaccesiblewidgets qtracegraphicssystem qtquickcontrolsplugin qtquickextrasflatplugin)'
#],
#'libraries': [
#    '<!@(pkg-config --libs-only-l Qt5QmlModels QtGui QtXml QtSql QtCore QtDBus Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets Qt5Quick Qt5Qml Qt5Sql Qt5Svg Qt5Xml Qt5DBus Qt5Help Qt5OpenGL Qt5Script Qt5WebKit Qt5XcbQpa Qt5CLucene Qt5Network Qt5Designer Qt5UiTools QtCLucene QtNetwork Qt5QuickTest Qt5X11Extras QtScript Qt5Concurrent Qt5FeedBack Qt5QmlDevTools QtOrganizer Qt5ScriptTools Qt5XmlPatterns Qt5PrintSupport Qt5QuickWidgets QtDeclarative QtXmlPatterns Qt5Organizer Qt5Positioning Qt5WebKitWidgets Qt5PlatformSupport Qt5QuickParticles Qt5OpenGLExtensions Qt5MultimediaQuick_p Qt5MultimediaWidgets Qt5DesignerComponents Qt5EglDeviceIntegration qtga qtiff qtwcodecs qtscriptdbus qtfeedback_mmk qtquick2plugin qtuiotouchplugin qtorganizer_memory qtaccesiblewidgets qtracegraphicssystem qtquickcontrolsplugin qtquickextrasflatplugin)'
#]