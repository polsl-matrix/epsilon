#pragma once

namespace epsilon::core::event {
    template<typename... Args>
    class Observer {
    public:
        virtual void Attached();
        virtual void Detached();

        virtual void Update(Args...) = 0;
    };
}
