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
    bool IsFullScreen;
    bool IsIsometric;
};

struct CharaterStateConfig
{
    int AnimSheetRows;
    int AnimSheetCols;
    int FirstSpriteRow;
    int FirstSpriteCol;
    int FrameCount;
    int AnimSpeed;
    SDL_RendererFlip Flip;
    bool Repeat;
    std::map<CharacterDirection, SDL_Texture*> DirectionMap;
};

struct CharacterTexturesConfig
{
    float XScale;
    float YScale;
    std::map<CharacterState, CharaterStateConfig*> StateMap;
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

    std::string windowParamsDefaultXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                         "<config>\n"
                                         "    <build version=\"0.1\" channel=\"dev\"/>\n"
                                         "    <meta name=\"Pelageia Immersive\" isometric=\"true\"/>\n"
                                         "    <window width=\"512\" height=\"512\" fullscreen=\"false\"/>\n"
                                         "</config>";

    std::string charactersTexturesParamsXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                              "<config>\n"
                                              "    <character id=\"Player\" xScale=\"1\" yScale=\"1\">\n"
                                              "        <state id=\"0\" animSheetRows=\"4\" animSheetCols=\"4\" firstSpriteRow=\"1\" firstSpriteCol=\"1\" frameCount=\"14\" animSpeed=\"280\" repeat=\"true\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Idle/Idle_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Idle/Idle_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Idle/Idle_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Idle/Idle_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Idle/Idle_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Idle/Idle_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Idle/Idle_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Idle/Idle_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"1\" animSheetRows=\"3\" animSheetCols=\"4\" firstSpriteRow=\"1\" firstSpriteCol=\"1\" frameCount=\"9\" animSpeed=\"180\" repeat=\"true\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Walk/Walk_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Walk/Walk_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Walk/Walk_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Walk/Walk_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Walk/Walk_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Walk/Walk_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Walk/Walk_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Walk/Walk_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"2\" animSheetRows=\"2\" animSheetCols=\"4\" firstSpriteRow=\"1\" firstSpriteCol=\"1\" frameCount=\"5\" animSpeed=\"100\" repeat=\"true\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Run/Run_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Run/Run_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Run/Run_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Run/Run_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Run/Run_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Run/Run_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Run/Run_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Run/Run_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"3\" animSheetRows=\"3\" animSheetCols=\"4\" firstSpriteRow=\"1\" firstSpriteCol=\"1\" frameCount=\"11\" animSpeed=\"220\" repeat=\"false\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Jump/Jump_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Jump/Jump_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Jump/Jump_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Jump/Jump_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Jump/Jump_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Jump/Jump_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Jump/Jump_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Jump/Jump_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"4\" animSheetRows=\"2\" animSheetCols=\"4\" firstSpriteRow=\"1\" firstSpriteCol=\"1\" frameCount=\"8\" animSpeed=\"160\" repeat=\"false\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/RunningJump/RunningJump_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "        <state id=\"5\" animSheetRows=\"3\" animSheetCols=\"4\" firstSpriteRow=\"1\" firstSpriteCol=\"1\" frameCount=\"10\" animSpeed=\"200\" repeat=\"false\" flip=\"0\">\n"
                                              "            <direction id=\"0\" filePath=\"Resources/Animations/Player/Roll/Roll_Up.png\"/>\n"
                                              "            <direction id=\"1\" filePath=\"Resources/Animations/Player/Roll/Roll_UpRight.png\"/>\n"
                                              "            <direction id=\"2\" filePath=\"Resources/Animations/Player/Roll/Roll_Right.png\"/>\n"
                                              "            <direction id=\"3\" filePath=\"Resources/Animations/Player/Roll/Roll_DownRight.png\"/>\n"
                                              "            <direction id=\"4\" filePath=\"Resources/Animations/Player/Roll/Roll_Down.png\"/>\n"
                                              "            <direction id=\"5\" filePath=\"Resources/Animations/Player/Roll/Roll_DownLeft.png\"/>\n"
                                              "            <direction id=\"6\" filePath=\"Resources/Animations/Player/Roll/Roll_Left.png\"/>\n"
                                              "            <direction id=\"7\" filePath=\"Resources/Animations/Player/Roll/Roll_UpLeft.png\"/>\n"
                                              "        </state>\n"
                                              "    </character>\n"
                                              "</config>";
};

#endif  // PELAGEIA_IMMERSIVE_CONFIGLOADER_H
