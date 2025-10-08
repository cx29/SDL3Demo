//
// Created by 二九 on 2025/10/8.
//

#pragma once
#ifndef SDL3DEMO_IPANEL_H
#define SDL3DEMO_IPANEL_H

class IPanel {
public:
    virtual ~IPanel() = default;

    virtual void Init(int width, int height) = 0;

    virtual void Update(float delta_seconds) = 0;

    virtual void Render() = 0;

    virtual const char *GetName() const = 0;
};


#endif //SDL3DEMO_IPANEL_H
