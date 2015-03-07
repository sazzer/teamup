#include "ui/windows/log.h"
#include "log/logstore.h"

namespace Teamup {
    namespace UI {
        namespace Windows {
            void LogWindow::operator()(Teamup::UI::WindowRenderer& renderer) {
                const unsigned int count = Teamup::Log::count();
                for (unsigned int i = 0; i < count; ++i) {
                    renderer.renderString(0, i, Teamup::Log::message(i));
                }
            }
        }
    }
}
