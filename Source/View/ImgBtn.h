#ifndef _IMG_BUTTON_
#define _IMG_BUTTON_

#include "../App/global.h"

class ImgBtn {
    public:
    ImgBtn(std::string fName, BUILD_TYPES actionId, Rectangle rect, std::string helpText) : _fName(fName), aID(actionId), _rect(rect), _helpText(helpText) {
        // TODO: img load
    };

    bool isClicked();
    BUILD_TYPES GetBuildID() { return aID; }

    void Render(bool active=false);
    void RenderText();
    private:
    std::string _fName;
    BUILD_TYPES aID;
    Rectangle _rect;
    std::string _helpText;
    int hover = 0;
};

#endif
