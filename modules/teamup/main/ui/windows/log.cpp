#include "ui/windows/log.h"
#include "flux/stores.h"
#include "log/logstore.h"

namespace Teamup {
    namespace UI {
        namespace Windows {
            void LogWindow::operator()(Teamup::UI::WindowRenderer& renderer) {
                const Teamup::Log::LogStore& logStore = Teamup::Flux::stores().getStore<Teamup::Log::LogStore>("log");

                const unsigned int count = logStore.count();
                for (unsigned int i = 0; i < count; ++i) {
                    renderer.renderString(0, i, logStore.message(i));
                }
            }
        }
    }
}
