#ifndef _IMG_BUTTON_
#define _IMG_BUTTON_

#include "../App/global.h"

class ImgBtn {
    public:
    ImgBtn(std::string fName, FIELD_TYPES actionId, Rectangle rect, std::string helpText) : _fName(fName), aID(actionId), _rect(rect), _helpText(helpText) {
        // TODO: img load
    };

    bool isClicked();
    FIELD_TYPES GetBuildID() { return aID; }

    void Render(bool active=false);
    private:
    std::string _fName;
    FIELD_TYPES aID;
    Rectangle _rect;
    std::string _helpText;
    int hover = 0;
};

#endif
