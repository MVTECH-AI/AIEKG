

#ifndef mitkPluginActivator_h
#define mitkPluginActivator_h

#include <ctkPluginActivator.h>

namespace mitk {

class myappnameactivator :
  public QObject, public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)

public:

  void start(ctkPluginContext* context);
  void stop(ctkPluginContext* context);

}; // $(activator-class-name)

}

#endif // $(activator-file-name)_h
