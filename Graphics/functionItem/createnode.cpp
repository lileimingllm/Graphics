#include "createnode.h"

ItemWindow *CreateNode::create(ClassParam param)
{
    ItemWindow * window = new ItemWindow(param);
    window->saveSelf(window);
    window->setFuncName(param.ObjectName);
    InputItem * input{ nullptr };
    OutputItem * output { nullptr };
    switch (param.type) {
    case ONLY_INPUT:
        input = new InputItem(param.InFieldtype,param.infielddsc, window);
        if (FIELD_TYPE::CUSTOM == param.InFieldtype){
            input->setWidget(param.InCustomWidget);
        }
        if (param.reg)input->getField()->setReg(param.reg);
        window->addInput(input);
        break;
    case EVENT:
        window->setTitleStyle ("background: rgb(100,12,24)");
        output = new OutputItem(param.OutFieldtype,QStringList()<<"事件输出",window);
        if (FIELD_TYPE::CUSTOM == param.OutFieldtype){
            output->setWidget(param.OutCustomWidget);
        }
        if (param.reg)output->getField()->setReg(param.reg);
        window->addOutput(output);
        break;
    case FIRST:
        window->setTitleStyle ("background:rgb(152, 31, 24)");
    case ONLY_OUTPUT:
        output = new OutputItem(param.OutFieldtype,param.outfielddsc,window);
        if (FIELD_TYPE::CUSTOM == param.OutFieldtype){
            output->setWidget(param.OutCustomWidget);
        }
        if (param.reg)output->getField()->setReg(param.reg);
        window->addOutput(output);
        break;
    case INPUT_OUTPUT:
        input = new InputItem(param.InFieldtype,param.infielddsc,window);
        if (FIELD_TYPE::CUSTOM == param.InFieldtype){
            input->setWidget(param.InCustomWidget);
        }
        if (param.reg)input->getField()->setReg(param.reg);
        window->addInput(input);
        output = new OutputItem(param.OutFieldtype,param.outfielddsc,window);
        if (FIELD_TYPE::CUSTOM == param.OutFieldtype){
            output->setWidget(param.OutCustomWidget);
        }
        if (param.reg)output->getField()->setReg(param.reg);
        window->addOutput(output);
        break;
    case OTHER:

        break;
    default:
        break;
    }
    return window;
}
