#include "ui/windows/log.h"
#include "flux/stores.h"
#include "log/logstore.h"

namespace Teamup {
    namespace UI {
        namespace Windows {
            void LogWindow::operator()(Teamup::UI::WindowRenderer& renderer) {
                const Teamup::Log::LogStore& logStore = Teamup::Flux::stores().getStore<Teamup::Log::LogStore>("log");

                renderer.renderString(0, 0, "Hello, World");
            }
        }
    }
}
