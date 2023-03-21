#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

class UiScreenView_Text;
//this is a singleton, and stores the Physics Engine script
class UiEngine
{
private:
    std::vector<UiScreenView_Text*> allScreenViewTexts;

    static UiEngine* instance;

    UiEngine();

    ~UiEngine();
public:

    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static UiEngine* GetInstance();

    inline void AddUiScreenViewTextToUiEngine(UiScreenView_Text* UiScreenView_Text_newText) { allScreenViewTexts.push_back(UiScreenView_Text_newText); };

    void DrawAllUi(sf::RenderWindow* _GameEngineWindow);
};
