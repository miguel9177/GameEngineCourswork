#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

class UiScreenView_Text;
class UiScreenView_Image;
class UiScreenView_btnImage;
//this is a singleton, and stores the Physics Engine script
class UiEngine
{
private:
    std::vector<UiScreenView_Text*> allScreenViewTexts;
    std::vector<UiScreenView_Image*> allScreenViewImages;
    std::vector<UiScreenView_btnImage*> allScreenViewBtnImages;

    static UiEngine* instance;

    UiEngine();

    ~UiEngine();
public:

    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static UiEngine* GetInstance();

    inline void AddUiScreenViewTextToUiEngine(UiScreenView_Text* UiScreenView_Text_newText) { allScreenViewTexts.push_back(UiScreenView_Text_newText); };
    inline void AddUiScreenViewImageToUiEngine(UiScreenView_Image* UiScreenView_Image_newImage) { allScreenViewImages.push_back(UiScreenView_Image_newImage); };
    inline void AddUiScreenViewButtonImageToUiEngine(UiScreenView_btnImage* UiScreenView_ButtonImage_newBtnImage) { allScreenViewBtnImages.push_back(UiScreenView_ButtonImage_newBtnImage); };

    void DrawAllUi(sf::RenderWindow* _GameEngineWindow);
};
