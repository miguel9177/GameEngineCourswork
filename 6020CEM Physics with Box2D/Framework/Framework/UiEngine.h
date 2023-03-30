#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

class UiScreenView_Text;
class UiScreenView_Image;
class UiScreenView_btnImage;
class UiScreenView_btnText;
//this is a singleton, and stores the Physics Engine script
class UiEngine
{
private:
    //stores all engine uis
    std::vector<UiScreenView_Text*> allScreenViewTexts;
    std::vector<UiScreenView_Image*> allScreenViewImages;
    std::vector<UiScreenView_btnImage*> allScreenViewBtnImages;
    std::vector<UiScreenView_btnText*> allScreenViewBtnTexts;

    //stores its instance since this is a singleton
    static UiEngine* instance;

    UiEngine();

    ~UiEngine();
public:

    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static UiEngine* GetInstance();

    //all this functions adds the specific ui to their specific vector
    inline void AddUiScreenViewTextToUiEngine(UiScreenView_Text* UiScreenView_Text_newText) { allScreenViewTexts.push_back(UiScreenView_Text_newText); };
    inline void AddUiScreenViewImageToUiEngine(UiScreenView_Image* UiScreenView_Image_newImage) { allScreenViewImages.push_back(UiScreenView_Image_newImage); };
    inline void AddUiScreenViewButtonImageToUiEngine(UiScreenView_btnImage* UiScreenView_ButtonImage_newBtnImage) { allScreenViewBtnImages.push_back(UiScreenView_ButtonImage_newBtnImage); };
    inline void AddUiScreenViewButtonTextToUiEngine(UiScreenView_btnText* UiScreenView_ButtonText_newBtnText) { allScreenViewBtnTexts.push_back(UiScreenView_ButtonText_newBtnText); };

    //all this functions removes the specific ui of their specific vector
    inline void RemoveUiScreenViewTextFromUiEngine(UiScreenView_Text* UiScreenView_Text_newText) 
    { 
        auto it = std::find(allScreenViewTexts.begin(), allScreenViewTexts.end(), UiScreenView_Text_newText);
      
        if (it != allScreenViewTexts.end())
            allScreenViewTexts.erase(it);
    };
    inline void RemoveUiScreenViewImageFromUiEngine(UiScreenView_Image* UiScreenView_Image_newImage)
    {
        auto it = std::find(allScreenViewImages.begin(), allScreenViewImages.end(), UiScreenView_Image_newImage);

        if (it != allScreenViewImages.end())
            allScreenViewImages.erase(it);
    };
    inline void RemoveUiScreenViewButtonImageFromUiEngine(UiScreenView_btnImage* UiScreenView_ButtonImage_newBtnImage)
    {
        auto it = std::find(allScreenViewBtnImages.begin(), allScreenViewBtnImages.end(), UiScreenView_ButtonImage_newBtnImage);

        if (it != allScreenViewBtnImages.end())
            allScreenViewBtnImages.erase(it);
    };
    inline void RemoveUiScreenViewButtonTextFromUiEngine(UiScreenView_btnText* UiScreenView_ButtonText_newBtnText)
    {
        auto it = std::find(allScreenViewBtnTexts.begin(), allScreenViewBtnTexts.end(), UiScreenView_ButtonText_newBtnText);

        if (it != allScreenViewBtnTexts.end())
            allScreenViewBtnTexts.erase(it);
    };

    //updates the ui
    void Update();
    //draws all ui
    void DrawAllUi(sf::RenderWindow* _GameEngineWindow);
};
