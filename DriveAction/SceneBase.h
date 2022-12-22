#pragma once

enum class SceneType
{
    TITLE,
    PLAY,
    RESULT
};

class SceneBase abstract
{
public:
    SceneBase(SceneType _SceneType) { nowScenType = _SceneType; }
    virtual ~SceneBase() {}

    virtual SceneType Update() = 0;
    virtual void Draw() = 0;
protected:
    SceneType nowScenType;
};