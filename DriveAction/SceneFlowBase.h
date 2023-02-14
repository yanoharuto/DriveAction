#pragma once
/// <summary>
/// ƒV[ƒ“‚²‚Æ‚Ìˆ—‚Ì—¬‚ê
/// </summary>
class SceneFlowBase abstract
{
public:
    SceneFlowBase() { isEndProccess = false; };
    virtual ~SceneFlowBase() {
        int a = 0;
    };
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    bool GetIsEndProccess() { return isEndProccess; };
protected:
    bool isEndProccess = false;
};