#ifndef _IMG_BUTTON_
#define _IMG_BUTTON_

#include "../App/global.h"

class ImgBtn {
    public:
    ImgBtn(std::string fName, int actionId, Rectangle rect, std::string helpText) : _fName(fName), aID(actionId), _rect(rect), _helpText(helpText) {
        // TODO: img load
    };

    bool isClicked();
    int GetBuildID() { return aID; }

    void Render();
    private:
    std::string _fName;
    int aID;
    Rectangle _rect;
    std::string _helpText;
    int hover = 0;
};

#endif
