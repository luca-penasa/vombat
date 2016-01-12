#pragma once
#ifndef Cropper_H
#define Cropper_H

#include "BaseFilter.h"

class CropperDlg;
class ccVirtualOutcrop;

class Cropper : public BaseFilter {
public:
    Cropper(ccPluginInterface* parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected();

    int openInputDialog();


    CropperDlg * m_dialog;

    ccVirtualOutcrop * m_root_outcrop;
};

#endif // Cropper_H
