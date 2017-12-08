

#include "mitkPluginActivator.h"

#include <QtPlugin>

#include "QmitkTemplateView.h"

namespace mitk {

void myappnameactivator::start(ctkPluginContext* context)
{
  BERRY_REGISTER_EXTENSION_CLASS(MypluginNameUIControl, context)
}

void myappnameactivator::stop(ctkPluginContext* context)
{
  Q_UNUSED(context)
}

}

Q_EXPORT_PLUGIN2(zhi.huang.plugin1, mitk::myappnameactivator)
