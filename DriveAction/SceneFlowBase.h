#pragma once
/// <summary>
/// �V�[�����Ƃ̏����̗���
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