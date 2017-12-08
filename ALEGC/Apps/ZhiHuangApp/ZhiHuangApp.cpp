

#include <berryStarter.h>
#include <Poco/Util/MapConfiguration.h>

#include <QApplication>

int main(int argc, char** argv)
{
  // Create a QApplication instance first
  QApplication myApp(argc, argv);
  myApp.setApplicationName("ZhiHuangApp");
  myApp.setOrganizationName("2");

  // These paths replace the .ini file and are tailored for installation
  // packages created with CPack. If a .ini file is presented, it will
  // overwrite the settings in MapConfiguration
  Poco::Path basePath(argv[0]);
  basePath.setFileName("");

  Poco::Path provFile(basePath);
  provFile.setFileName("ZhiHuangApp.provisioning");

  Poco::Util::MapConfiguration* sbConfig(new Poco::Util::MapConfiguration());
  sbConfig->setString(berry::Platform::ARG_PROVISIONING, provFile.toString());
  sbConfig->setString(berry::Platform::ARG_APPLICATION, "org.mitk.qt.extapplication");
  return berry::Starter::Run(argc, argv, sbConfig);
}
