#pragma once
class SceneFlowBase abstract
{
public:
    SceneFlowBase() { isEndProccess = false; };
    ~SceneFlowBase() {};
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    bool GetIsEndProccess() { return isEndProccess; };
protected:
    bool isEndProccess;
};