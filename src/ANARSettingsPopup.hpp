#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ANARSettingsPopup : public Popup<> {
protected:
    int m_value;
    bool m_enabled;
    TextInput* m_percentageInput;
    CCMenuItemSpriteExtra* m_leftButton;
    CCMenuItemSpriteExtra* m_rightButton;
    Slider* m_slider;

    bool setup() override;
    void onSlider(CCObject* sender);
    void valueChanged(bool updateText);
public:
    static ANARSettingsPopup* create();
};
