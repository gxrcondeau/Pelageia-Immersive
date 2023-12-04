//
// Created by gxrcondeau on 2023-10-08.
//

#ifndef PELAGEIA_IMMERSIVE_CONFIGLOADER_H
#define PELAGEIA_IMMERSIVE_CONFIGLOADER_H

#include "SDL.h"
#include <map>
#include <cstdint>
#include "pugixml.hpp"
#include "Characters/Character.h"

struct WindowConfig
{
    std::string Name;
    int Width;
    int Height;
    bool FullScreen;
};

struct CharacterTexturesConfig
{
    std::uint8_t AnimSheetRows;
    std::uint8_t AnimSheetCols;
    std::uint8_t StartSpriteRow;
    std::uint8_t FrameCount;
    std::uint8_t AnimSpeed;
    SDL_RendererFlip Flip;
    std::map<CharacterState, std::map<CharacterDirection, std::string>> TextureMap;
};

class ConfigLoader
{
public:
    static ConfigLoader* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new ConfigLoader()); }

    WindowConfig* GetWindowConfig();
    std::map<std::string, CharacterTexturesConfig*> GetCharactersTexturesConfig();

    void CreateConfig(std::string configName, std::string configXml) const;

protected:
    const std::string ConfigDirectory = "./Config/";
    const std::string WindowParamsFileName = "WindowConfig.xml";
    const std::string CharacterTextureParamsFileName = "CharactersTexturesConfig.xml";

    pugi::xml_document GetConfigXml(std::string configName) const;

    bool IsDirectoryExist() const;
    bool IsFileExist(std::string configName) const;

private:
    ConfigLoader();
    static ConfigLoader* s_Instance;

    WindowConfig* windowConfig = nullptr;
    std::map<std::string, CharacterTexturesConfig*> charactersTexturesConfig;

    std::string windowParamsDefaultXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                         "<config>\n"
                                         "    <build version=\"0.1\" channel=\"dev\"/>\n"
                                         "    <meta name=\"Pelageia Immersive\"/>\n"
                                         "    <window width=\"512\" height=\"512\" fullscreen=\"0\"/>\n"
                                         "</config>";

    std::string charactersTexturesParamsXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                              "<config>\n"
                                              "    <character id=\"Player\">\n"
                                              "        <state id=\"0\" animSheetRows=\"4\" animSheetCols=\"4\" startSpriteRow=\"1\" frameCount=\"14\" animSpeed=\"75\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Idle/Idle_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Idle/Idle_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Idle/Idle_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Idle/Idle_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Idle/Idle_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Idle/Idle_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Idle/Idle_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Idle/Idle_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"1\" animSheetRows=\"3\" animSheetCols=\"4\" startSpriteRow=\"1\" frameCount=\"9\" animSpeed=\"100\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Walk/Walk_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Walk/Walk_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Walk/Walk_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Walk/Walk_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Walk/Walk_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Walk/Walk_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Walk/Walk_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Walk/Walk_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"2\" animSheetRows=\"2\" animSheetCols=\"4\" startSpriteRow=\"1\" frameCount=\"5\" animSpeed=\"75\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Run/Run_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Run/Run_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Run/Run_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Run/Run_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Run/Run_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Run/Run_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Run/Run_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Run/Run_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "    </character>\n"
                                              "</config>";
};

#endif  // PELAGEIA_IMMERSIVE_CONFIGLOADER_H
