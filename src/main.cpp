#include "ANARSettingsPopup.hpp"

#include <Geode/modify/PlayLayer.hpp>
class $modify(ANARPlayLayer, PlayLayer) {
    void resetLevel() {
        PlayLayer::resetLevel();

        if (auto popup = getChildOfType<ANARSettingsPopup>(CCDirector::sharedDirector()->getRunningScene(), 0)) {
            popup->setKeypadEnabled(false);
            popup->setTouchEnabled(false);
            popup->removeFromParentAndCleanup(true);
        }
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        auto GM = GameManager::sharedState();
        auto autoRetryEnabled = GM->getGameVariable("0026");
        if (!autoRetryEnabled) {
            PlayLayer::destroyPlayer(player, object);
            return;
        }

        if (!m_isPracticeMode && !player->m_isPlatformer && Mod::get()->getSettingValue<bool>("enable") &&
            getCurrentPercentInt() >= Mod::get()->getSettingValue<int64_t>("percentage")) GM->setGameVariable("0026", false);

        PlayLayer::destroyPlayer(player, object);

        GM->setGameVariable("0026", autoRetryEnabled);
    }
};

#include <Geode/modify/PauseLayer.hpp>
class $modify(ANARPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        if (GameManager::sharedState()->m_playLayer->m_levelSettings->m_platformerMode) return;

        auto rightButtonMenu = getChildByID("right-button-menu");
        auto anarButtonSprite = CircleButtonSprite::createWithSprite("ANAR_anarBtn_001.png"_spr, 1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
        anarButtonSprite->getTopNode()->setScale(1.0f);
        anarButtonSprite->setScale(0.6f);
        rightButtonMenu->addChild(CCMenuItemExt::createSpriteExtra(anarButtonSprite, [](auto) { ANARSettingsPopup::create()->show(); }));
        rightButtonMenu->updateLayout();
    }
};
