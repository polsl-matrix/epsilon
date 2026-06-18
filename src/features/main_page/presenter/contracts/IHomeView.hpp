#pragma once

class IHomeView {
public:
    virtual ~IHomeView() = default;
    virtual void ShowLogoutSuccess() = 0;
};