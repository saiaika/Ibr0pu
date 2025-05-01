#include "SDK.hpp"
#include "Resources/Includes.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Tools.h"
#include "fake_dlfcn.h"
#include "StrEnc.h"
#include "plthook.h"
#include "obfuscate.h"
#include "Rect.h"
#include "Quaternion.hpp"
#include "Colors.h"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Resources/Color.h"
#include "FTools/timer.h"
#include "Resources/Yala.h"
#include "fontch.h"
#define SLEEP_TIME 1000LL / 60LL
using namespace SDK;
#include <curl/curl.h>
#include <openssl/rsa.h>
bool TeamNrg1;
#include <openssl/pem.h>
#include "Resources/base64/base64.h"
#include "UI.h" 
#include "Font.h" 
#include <cstring>
#include <string.h>
#include "imgui/imgui_internal.h"
#include "Resources/FONTS/Fatih.h"
#include "Resources/FONTS/New.h"
#include "Resources/ITEMS/Items.h"
#include "Resources/ITEMS/json.hpp"
#include "Resources/ITEMS/Item.h"
#include "Resources/ITEMS/Itemsmg.h"
#include "Resources/ITEMS/ItemSni.h"
#include "Resources/ITEMS/Heal.h"
#include "Resources/ITEMS/Itemsammo.h"
#include "Resources/ITEMS/Itemsmag.h"
#include "Resources/ITEMS/Itemscope.h"
#include "Resources/Oxorany/oxorany.h"
#include "hook/Substrate/SubstrateHook.h"
#include "Resources/KittyMemory/MemoryPatch.h"
#include "Includes/Macros.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"

#include "Hook.h"

using json = nlohmann::json;
static int helmett3 = 0;
static int bag3 = 0;
int modM4 = 101004;
int modAKM = 101001;
static bool out = true;
static int Luminous = 0;
static bool GunS;
static bool VehS;
static bool FileS;
bool autoM = false;
float autoMY = 115.0f;
static int modXsuit = 1400129;
bool ModSkinn = false;
bool KillMessage = false;
bool LobbySkin = false;
#include "jsonPreferences.h"
int sEmote1 = 2200101;
int sEmote2 = 2200201;
int sEmote3 = 2200301;
bool ModSkinnn = false;
timer RenderingFPS;
int ModEmote1 = 0;
namespace Active {
  inline int SkinCarDefault = 0;
  inline int SkinCarMod = 0;
  inline int SkinCarNew = 0;
}
#include "Loading.h"
#include "X2.h"
int TABG = 1;
#define TSL_FONT_DEFAULT_SIZE 20
static UFont *tslFont = 0, *robotoTinyFont = 0;

#define IM_PI                   3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))



void IMGUI_GOD(FRotator &angles) {
    if (angles.Pitch > 180)
        angles.Pitch -= 360;
    if (angles.Pitch < -180)
        angles.Pitch += 360;
    if (angles.Pitch < -75.f)
        angles.Pitch = -75.f;
    else if (angles.Pitch > 75.f)
        angles.Pitch = 75.f;
    while (angles.Yaw < -180.0f)
        angles.Yaw += 360.0f;
    while (angles.Yaw > 180.0f)
        angles.Yaw -= 360.0f;
}
void IMGUI_GOD(float *angles) {
    if (angles[0] > 180)
        angles[0] -= 360;
    if (angles[0] < -180)
        angles[0] += 360;
    if (angles[0] < -75.f)
        angles[0] = -75.f;
    else if (angles[0] > 75.f)
        angles[0] = 75.f;
    while (angles[1] < -180.0f)
        angles[1] += 360.0f;
    while (angles[1] > 180.0f)
        angles[1] -= 360.0f;
}
void IMGUI_GOD(Vector3 angles) {
    if (angles.X > 180)
        angles.X -= 360;
    if (angles.X < -180)
        angles.X += 360;
    if (angles.X < -75.f)
        angles.X = -75.f;
    else if (angles.X > 75.f)
        angles.X = 75.f;
    while (angles.Y < -180.0f)
        angles.Y += 360.0f;
    while (angles.Y > 180.0f)
        angles.Y -= 360.0f;
}long GetEpochTime()
    {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }


    
 uintptr_t ProcessEvent_Offset;
//====================#BY @JOHANLIBERT @REOHECKS====================//
#define GNames_Offset 0x76f0f18
#define GEngine_Offset 0xd7c6170//ULocalPlayer
#define GEngine_Offset 0xd7eb2e8//UEngine
#define GUObject_Offset 0xd4af4b0
#define GetActorArray 0x976d438
#define GNativeAndroidApp_Offset 0xd218550
#define GetActorArray_Offset 0x994dc6c
#define Canvas_Map_Offset 0xd218b98
#define ProccesEvent_Offset 0x7952c80//Child
#define ProccesEvent_Offset 0x92d5034//Main
#define Actors_Offset 0xA0
#define LootBox_Offset 0x848 + 0x4
//====================#MADE BY @JOHANLIBERT @REOHECKS====================//
#define ShortEvent_Offset 168 //Not Sure






uintptr_t anort;
uintptr_t ANOGS;
uintptr_t UE4;
uintptr_t g_UE4;
uintptr_t Anogs;
uintptr_t gcloud;
uintptr_t g_Anogs;
uintptr_t g_gcloud;
uintptr_t PandoraVideo;
uintptr_t GKPxStudio;
uintptr_t tgpa;
uintptr_t cubehawk;
uintptr_t shared;
uintptr_t INTLFoundation;
uintptr_t INTLCompliance;
uintptr_t CrashSight;
uintptr_t antiban;
uintptr_t GCloudVoice;
uintptr_t ijkffmpeg;
uintptr_t gcloudcore;
uintptr_t gnustl_shared;
uintptr_t igshare;
uintptr_t ITOP;
uintptr_t marsxlog;
uintptr_t swappy;
uintptr_t GvoiceNN;
uintptr_t TDataMaster;
uintptr_t g_cloud;
UWorld *GEWorld;
int GWorldNum = 0;
TUObjectArray gobjects;
UWorld *GetWorld()
{
    if(GWorldNum == 0) {
        gobjects = UObject::GUObjectArray->ObjObjects;
        for (int i=0; i< gobjects.Num(); i++)
            if (auto obj = gobjects.GetByIndex(i)) {
                if(obj->IsA(UEngine::StaticClass())) {
                    auto GEngine = (UEngine *) obj;
                    if(GEngine) {
                        auto ViewPort = GEngine->GameViewport;
                        if (ViewPort)
                        {
                            GEWorld = ViewPort->World;
                            GWorldNum = i;
                            return ViewPort->World;
                        }
                    }
                }
            }
    }else {
        auto GEngine = (UEngine *) (gobjects.GetByIndex(GWorldNum));
        if(GEngine) {
            auto ViewPort = GEngine->GameViewport;
            if(ViewPort) {
                GEWorld = ViewPort->World;
                return ViewPort->World;
            }
        }
    }
    return 0;
}


TNameEntryArray *GetGNames() {
return ((TNameEntryArray *(*)()) (UE4 + GNames_Offset))();}
std::vector<AActor *> getActors() {
auto World = GetWorld();
if (!World)
return std::vector<AActor *>();
auto PersistentLevel = World->PersistentLevel;
if (!PersistentLevel)
return std::vector<AActor *>();
struct GovnoArray {
uintptr_t base;
int32_t count;
int32_t max;};
static thread_local GovnoArray Actors{};
Actors = *(((GovnoArray*(*)(uintptr_t))(UE4 + GetActorArray))(reinterpret_cast<uintptr_t>(PersistentLevel)));
if (Actors.count <= 0) {return {};}
std::vector<AActor *> actors;
for (int i = 0; i < Actors.count; i++) {
auto Actor = *(uintptr_t *) (Actors.base + (i * sizeof(uintptr_t)));
if (Actor) {
actors.push_back(reinterpret_cast<AActor *const>(Actor));
}}return actors;}
struct sRegion {uintptr_t start, end;};
std::vector<sRegion> trapRegions;
bool isObjectInvalid(UObject *obj) {
if (!Tools::IsPtrValid(obj)) {return true;}
if (!Tools::IsPtrValid(obj->ClassPrivate)) {return true;}
if (obj->InternalIndex <= 0) {return true;}
if (obj->NamePrivate.ComparisonIndex <= 0) {return true;}
if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4) {return true;}
if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
return true;}return false;}
const char *getObjectPath(UObject *Object) {
std::string s;
for (auto super = Object->ClassPrivate; super; super = (UClass *) super->SuperStruct) {
if (!s.empty())
s += ".";
s += super->GetName();}return s.c_str();}




ImFont* F48 = nullptr;
ImFont* F50 = nullptr;
ImFont* JAAT = nullptr;
ImFont* SOCIAL = nullptr;


#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};
int32_t ToColor(float *col) {return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *) (col));}
float menu[4] = { 0/255.f, 255/255.f, 255/255.f, 1.000f };


 int screen_Width = 0, screen_Height = 0;
int screen_Density = 0;
    struct GovnoArray {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };
    static thread_local GovnoArray Actors{};
 
   // Actors = *(((GovnoArray*(*)(uintptr_t))(UE4 + GetActorArray))(reinterpret_cast<uintptr_t>(PersistentLevel)));
 

float AimSmooth = 1.0f;
bool Bypass;
float FOVT;
float FOVTB;
bool INFO;   
bool ESPINFO;
bool AIMBUTTON;
bool BTBUTTON;
bool active = false;
bool Skin_Menu;
bool Esp_Menuu;
bool Aim_Menuu;
bool Item_Menuu;
bool Skin_Menuu;
std::string g_Token, g_Auth;
bool bValid = false;
bool initImGui = false;
static std::string EXP = "00:00:00:00:00:00:00";
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;

#define COLOR_BLACK FLinearColor(0, 0, 0, 1.f)
#define COLOR_WHITE FLinearColor(1.f, 1.f, 1.f, 1.f)
#define COLOR_RED FLinearColor(1.f, 0, 0, 1.f)
#define COLOR_CAR FLinearColor(1.f, 0.5f, 1.f, 1.f)
#define COLOR_GREEN FLinearColor(0, 0.5f, 0, 1.f)
#define COLOR_ORANGE FLinearColor(1.f, 0.4f, 0, 1.f)
#define COLOR_YELLOW FLinearColor(1.f, 1.f, 0, 1.f)
#define COLOR_LIME FLinearColor(0, 1.f, 0, 1.f)
#define COLOR_BLUE FLinearColor(0, 0, 1.f, 1.f)
#define COLOR_THISTLE FLinearColor(1.0f, 0.74f, 0.84f, 1.0f)
#define COLOR_PINK FLinearColor(1.0f, 0.75f, 0.8f, 1.0f)
#define COLOR_YELOW FLinearColor(1.f, 1.f, 0, 1.f)
using json = nlohmann::json;
json items_data;
json items_data_r;
json items_data_sm;
json items_data_sn;
json items_data_h;
json items_data_ammo;
json items_data_mag;
json items_data_scop;
std::map<int, float *> ItemColors;
std::map<int, bool> Items;
bool PlayerMenu;
bool WeaponMenu;
bool VehicleMenu;             

enum EAim {Distance = 0,Croshhair = 1};
enum EAimTarget {Head = 0,Chest = 1};
enum EAimTrigger {Any = 0,Shooting = 1,Scoping = 2,Both = 3,None = 4};
enum EEspUI {UI1 = 0,UI2 = 1,UI3 = 2};
enum EFova {Fova1 = 0,Fova2 = 1,Fova3 = 2};
enum EFov {Fov1 = 0,Fov2 = 1,Fov3 = 2};
enum EEspPline {Top = 0,Mid = 1,Buttom = 2,eno1 = 3,};
enum EEspBline {Middle = 0,Up = 1,Low = 2,no = 3,};

//   float Crozn_Skins;
   float Face_Skin;
   float Bag_Skin;
   float Helmet_Skin;
   float Emote_Skin;
   float Parachute_Skin;
   float M416_Skin;
   float AKM_Skin;
   float SCARL_Skin;
   float M762_Skin;
   float GROZA_Skin;
   float AUG_Skin;
   float M16A4_Skin;
   float ACE32_Skin;
   float KAR98_Skin;
   float M24_Skin;
   float AWM_Skin;
   float DP28_Skin;
   float M249_Skin;
   float UZİ_Skin;
   float UMP_Skin;
   float THOMPSON_Skin;
   float VECTOR_Skin;
   float BİZON_Skin;
   float PAN_Skin;
   float Dacia_Skin;
   float Coupe_Skin;
   float UAZ_Skin;
   float MotoBike_Skin;
   float BigFoot_Skin;
   float Mirado_Skin;
   float Buggy_Skin;
   float PG117_Skin;
   float MiniBus_Skin;
  
    struct sConfig {
    int FPSControl;
float FPSControlSize;
bool HandCam;
        bool Bypass = true;
        bool AutoFiree;
        bool ShowVehicle1;
        float Hit;
        EFov TFov;
        float IpadS;
        EFova TFova;
        float Line;
        int Prid;
        float Skeleton;
        int RadarX;
        int RadarY;
		bool Linee;
		bool NoBot;
        int Loot;
   
    struct sAsp {
        EEspPline Pline;
        EEspBline Bline;
        EEspUI EUI;
        bool Line;
        bool Box;
        bool Radar;
        bool Skeleton;
        bool Health;
        bool LootBox;
        bool Name;
        bool Distance;
        bool Alert;
        bool TeamID;
        bool Air;
		bool Genn;
        bool Plane;
        bool Weapon;
        bool Gameİnfo;
        bool Vehicle;
        bool NoBot;
        bool FPS;
        bool Loot;};
    sAsp Asp;
    
    struct sHighRisk {
        bool Swim;
        bool Switch;
        bool Scope;
        bool FastMove;
        bool SuperAim;
        bool Unlock;
        bool NoFog;
        bool Shoot;
        bool Fly;
        bool Reload;
        bool HitRGB;
        bool Ipad;
        bool Prone;
        bool Ljump;
        bool Blockspect;
        bool Shake;
        bool Recoil;
        bool Instant;
		bool HitEffect;};
    sHighRisk HighRisk{0};
   
    struct sAimMenu {
        bool Enable;
        int Meter;
        bool Pov;
        bool Pred;
        bool Recoil;
        bool Aimbot;
        int Cross;
        int Position;
        float Recc;
        EAimTarget Target;
        EAimTrigger Trigger;
        bool IgnoreKnocked;
        bool VisCheck;
        bool IgnoreBots;
		bool TargetLine;};
    sAimMenu SilentAim{0};
    sAimMenu AimBot{0};
   
    struct sColorsESP {
        float *PlayerVisLine;
        float *PlayerHideLine;
        float *BotVisLine;
        float *BotHideLine;
        float *PlayerVisSkeleton;
        float *PlayerHideSkeleton;
        float *BotVisSkeleton;
        float *BotHideSkeleton;
        float *PlayerVisBox;
        float *PlayerHideBox;
        float *BotVisBox;
        float *BotHideBox;
        float *PlayerRadar;
        float *BotRadar;
        float *PlayerAlert;
        float *BotAlert;
        float *Fov;
        float *Fova;
        };
    sColorsESP ColorsESP{0};};
    sConfig Config{0};

   
    
#include "imgui/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "IMAGE/Aim_off.h"
#include "IMAGE/Aim_on.h"
#include "IMAGE/Un.h"
#include "IMAGE/X.h"
#include "IMAGE/logo.h"
#include "IMAGE/rg.h"
#include "IMAGE/lf.h"
    struct TextureInfo { ImTextureID textureId; int x; int y; int w; int h; };
    void DrawImage(int x, int y, int w, int h, ImTextureID Texture) {
    ImGui::GetForegroundDrawList()->AddImage(Texture, ImVec2(x, y), ImVec2(x + w, y + h));}
    
    static TextureInfo textureInfo;
    TextureInfo createTexture(char *ImagePath) {
    int w, h, n;
    stbi_uc *data = stbi_load(ImagePath, &w, &h, &n, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (n == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }stbi_image_free(data);
    textureInfo.textureId = reinterpret_cast<ImTextureID>((GLuint *) texture);
    textureInfo.w = w;
    textureInfo.h = h;
    return textureInfo;}
    TextureInfo CreateTexture(const unsigned char* buf, int len) {
    TextureInfo image;
    unsigned char* image_data = stbi_load_from_memory(buf, len, &image.w, &image.h, NULL, 0);
    if (image_data == NULL) {perror("File does not exist");}
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    #endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.w, image.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);
    image.textureId = (ImTextureID)image_texture;
    return image;}

TextureInfo Aim_off;
TextureInfo Aim_on;
TextureInfo Un;
TextureInfo lee;
TextureInfo rg;
TextureInfo lf;
TextureInfo X;
void InitTexture() {
Aim_off = CreateTexture(Aim_off_data, sizeof(Aim_off_data));
Aim_on = CreateTexture(Aim_on_data, sizeof(Aim_on_data));

Un = CreateTexture(Un_data, sizeof(Un_data));

X = CreateTexture(X_data, sizeof(X_data));
lee = CreateTexture(lee_data, sizeof(lee_data));

rg = CreateTexture(rg_data, sizeof(rg_data));
lf = CreateTexture(lf_data, sizeof(lf_data));
}


UGameplayStatics* GetGameplayStatics() {
 return (UGameplayStatics*)UGameplayStatics::StaticClass();
}
ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localPlayerController = 0;
        void (*orig_Broadcast)(ASTExtraPlayerController* thiz, struct FFatalDamageParameter* FatalDamageParameter);

			
void hk_Broadcast(ASTExtraPlayerController* thiz, struct FFatalDamageParameter* FatalDamageParameter)
{
	if (ModSkinn && KillMessage){
  if (g_LocalController->PlayerKey == FatalDamageParameter->CauserKey)
  {

   FatalDamageParameter->CauserClothAvatarID = new_Skin.XSuits;
  }
}
  return orig_Broadcast(thiz, FatalDamageParameter);
}
static int prevXSuits = preferences.Config.Skin.XSuits = 0;
static auto start = std::chrono::high_resolution_clock::now();
static bool callFunction = false;
static bool callNotify = false;
static bool callModSkin = false;
			
FRotator ToRotator(FVector local, FVector target) {
FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);
float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);
FRotator newViewAngle = {0};
newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
newViewAngle.Roll = (float) 0.f;
if (rotation.X >= 0.f)
newViewAngle.Yaw += 180.0f;
return newViewAngle;}
//==========
FVector WorldToRadar(float Yaw, FVector Origin, FVector LocalOrigin, float PosX, float PosY, Vector3 Size, bool &outbuff) {
bool flag = false;
double num = (double)Yaw;
double num2 = num * 0.017453292519943295;
float num3 = (float)std::cos(num2);
float num4 = (float)std::sin(num2);
float num5 = Origin.X - LocalOrigin.X;
float num6 = Origin.Y - LocalOrigin.Y;
struct FVector Xector;
Xector.X = (num6 * num3 - num5 * num4) / 150.f;
Xector.Y = (num5 * num3 + num6 * num4) / 150.f;
struct FVector Xector2;
Xector2.X = Xector.X + PosX + Size.X / 2.f;
Xector2.Y = -Xector.Y + PosY + Size.Y / 2.f;
bool flag2 = Xector2.X > PosX + Size.X;
if (flag2) {
Xector2.X = PosX + Size.X;
}else{
bool flag3 = Xector2.X < PosX;
if (flag3) {
Xector2.X = PosX;
}}
bool flag4 = Xector2.Y > PosY + Size.Y;
if (flag4) {
Xector2.Y = PosY + Size.Y;
}else{
bool flag5 = Xector2.Y < PosY;
if (flag5){
Xector2.Y = PosY;
}}
bool flag6 = Xector2.Y == PosY || Xector2.X == PosX;
if (flag6){
flag = true;}
outbuff = flag;
return Xector2;}
//==========
void VectorAnglesRadar(Vector3 & forward, FVector & angles) {
if (forward.X == 0.f && forward.Y == 0.f) {
angles.X = forward.Z > 0.f ? -90.f : 90.f;
angles.Y = 0.f;
} else {
angles.X = RAD2DEG(atan2(-forward.Z, forward.Magnitude(forward)));
angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
}angles.Z = 0.f;}
//===========



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        #define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)
        bool isInsideFOV(int x, int y) {
        if (!Config.SilentAim.Cross)
        return true;
        int circle_x = glWidth / 2;
        int circle_y = glHeight / 2;
        int rad = Config.SilentAim.Cross*0.5f;
        return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
        }
    
        auto GetTargetByCrossDist() {
        ASTExtraPlayerCharacter *result = 0;
        float max = std::numeric_limits<float>::infinity();
        auto Actors = getActors();
        auto localPlayer = g_LocalPlayer;
        auto localController = g_LocalController;
        if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
        auto Actor = Actors[i];
        if (isObjectInvalid(Actor))
        continue;
        if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
        auto Player = (ASTExtraPlayerCharacter *)Actor;
        auto Target = (ASTExtraPlayerCharacter *) Actor;
        float dist = localPlayer->GetDistanceTo(Target) / 100.0f;    
        if (dist > Config.SilentAim.Meter)
        continue;   
        if (Player->PlayerKey == localPlayer->PlayerKey)
        continue;
        if (Player->TeamID == localPlayer->TeamID)
        continue;
        if (Player->bDead)
        continue;
        if (Config.SilentAim.IgnoreKnocked) {
        if (Player->Health == 0.0f)
        continue;}
        if (Config.SilentAim.VisCheck) {
        if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
        continue;}
        if (Config.SilentAim.IgnoreBots) {
        if (Player->bEnsure)
        continue;}
        auto Root = Player->GetBonePos("Root", {});
        auto Head = Player->GetBonePos("Head", {});
        FVector2D RootSc, HeadSc;
        if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
        float height = abs(HeadSc.Y - RootSc.Y);
        float width = height * 0.65f;
        FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
        if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
        FVector2D v2Middle = FVector2D((float) (glWidth / 2), (float) (glHeight / 2));
        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);
        if (isInsideFOV((int) middlePoint.X, (int) middlePoint.Y)) {
        float dist = FVector2D::Distance(v2Middle, v2Loc);
        if (dist < max) {
        max = dist;
        result = Player;
        }}}}}}}return result;}
        
        bool isInsideFOVA(int x, int y) {
        if (!Config.AimBot.Cross)
        return true;
        int circle_x = glWidth / 2;
        int circle_y = glHeight / 2;
        int rad = Config.AimBot.Cross*0.5f;
        return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
        }
        auto GetTargetForAimBot() {
        ASTExtraPlayerCharacter *result = 0;
        float max = std::numeric_limits<float>::infinity();
        auto Actors = getActors();
        auto localPlayer = g_LocalPlayer;
        auto localController = g_LocalController;
        if (localPlayer) {
        for (auto Actor : Actors) {
        if (isObjectInvalid(Actor))
        continue;
        if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
        auto Player = (ASTExtraPlayerCharacter *) Actor;
        auto Target = (ASTExtraPlayerCharacter *) Actor;
        float dist = localPlayer->GetDistanceTo(Target) / 100.0f;    
        if (dist > Config.AimBot.Meter)
        continue;
        if (Player->PlayerKey == localPlayer->PlayerKey)
        continue;
        if (Player->TeamID == localPlayer->TeamID)
        continue;
        if (Player->bDead)
        continue;
        if (Config.AimBot.IgnoreKnocked) {
        if (Player->Health == 0.0f)
        continue;}
        if (Config.AimBot.VisCheck) {
        if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
        continue;}
        if (Config.AimBot.IgnoreBots) {
        if (Player->bEnsure)
        continue;}
        auto Root = Player->GetBonePos("Root", {});
        auto Head = Player->GetBonePos("Head", {});
        FVector2D RootSc, HeadSc;
        if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
        float height = abs(HeadSc.Y - RootSc.Y);
        float width = height * 0.65f;
        FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
        if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
        FVector2D v2Middle = FVector2D((float) (glWidth / 2), (float) (glHeight / 2));
        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);
        if (isInsideFOVA((int) middlePoint.X, (int) middlePoint.Y)) {
        float dist = FVector2D::Distance(v2Middle, v2Loc);
        if (dist < max) {
        max = dist;
        result = Player;
        }}}}}}}return result;}
        
    const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) {
    switch (Vehicle->VehicleShapeType) {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";
            break;
        default:
            return "Vehicle";
            break;
            }return "Vehicle";}
            
            
            
            
			template<class T>
void GetAllActors(std::vector<T *> &Actors) {
    UGameplayStatics *gGameplayStatics = (UGameplayStatics *) gGameplayStatics->StaticClass();
    auto GWorld = GetWorld();
    if (GWorld) {
        TArray<AActor *> Actors2;
        gGameplayStatics->GetAllActorsOfClass((UObject *) GWorld, T::StaticClass(), &Actors2);
        for (int i = 0; i < Actors2.Num(); i++) {
            Actors.push_back((T *) Actors2[i]);
        }
    }
}

FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName) {
    return Actor->GetBonePos(BoneName, FVector());
}

void DrawLine(AHUD *HUD, FVector2D posFrom, FVector2D posTo, float Thickness, FLinearColor Color) {
    HUD->DrawLine(posFrom.X, posFrom.Y, posTo.X, posTo.Y, Color, Thickness);
}

void DrawRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, float Thickness, FLinearColor Color) {
	HUD->DrawLine(Pos.X, Pos.Y, Pos.X + Width, Pos.Y, Color, Thickness);
	HUD->DrawLine(Pos.X, Pos.Y, Pos.X, Pos.Y + Height, Color, Thickness);
	HUD->DrawLine(Pos.X + Width, Pos.Y, Pos.X + Width, Pos.Y + Height, Color, Thickness);
	HUD->DrawLine(Pos.X, Pos.Y + Height, Pos.X + Width, Pos.Y + Height, Color, Thickness);
}
void DrawArrows( AHUD *HUD, FVector2D xy1, FVector2D xy2, FVector2D xy3,FVector2D xy4, FVector2D xy5 , FVector2D xy6 , FVector2D xy7 , float thickness, FLinearColor color) {
DrawLine( HUD,xy1, xy2, thickness ,color);
DrawLine( HUD,xy2, xy3, thickness ,color);
DrawLine( HUD,xy3, xy7, thickness ,color);
DrawLine( HUD,xy7, xy6, thickness ,color);
DrawLine( HUD,xy6, xy5, thickness ,color);
DrawLine( HUD,xy5, xy4, thickness ,color);
DrawLine( HUD,xy4, xy1, thickness ,color);

}
bool W2S2(FVector worldPos, FVector2D *screenPos) {
    return g_LocalController->ProjectWorldLocationToScreen(worldPos, true, screenPos);
}
static void DrawArrowsCrozn(AHUD *hud, std::array<FVector2D, 7> Loc, float thickness, FLinearColor color) {
    for (int i = 10; i < 25; i++) {
        DrawLine(hud, Loc.at(i), Loc.at(7), thickness, color);
    }
    for (int i = 26; i < 38; i++) {
        DrawLine(hud, Loc.at(i), Loc.at(7), thickness + 1.5, color);
        DrawLine(hud, Loc.at(i), Loc.at(8), thickness + 1.5f, color);
        DrawLine(hud, Loc.at(i), Loc.at(9), thickness + 1.5f, color);
    }
}

void DrawFilledRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, FLinearColor Color) {
	HUD->DrawRect(Color, Pos.X, Pos.Y, Width, Height);
}
void Line(AHUD *HUD,FVector2D origin, FVector2D dest, FLinearColor Color)
{
   HUD->DrawLine(origin.X, origin.Y, dest.X, dest.Y, Color, 2.0f);
}
void LineE(AHUD *HUD, FVector2D posFrom, FVector2D posTo, float Thickness, FLinearColor Color) {
    HUD->DrawLine(posFrom.X, posFrom.Y, posTo.X, posTo.Y, Color, Thickness);
}

void Box3D(AHUD *HUD, FVector origin, FVector extends, FLinearColor Color) {
    origin.X -= extends.X / 2.f;
    origin.Y -= extends.Y / 2.f;
    origin.Z -= extends.Z / 2.f;
    
    
 FVector one = origin;
 FVector two = origin; two.X += extends.X;
 FVector tree = origin; tree.X += extends.X; tree.Y += extends.Y;
 FVector four = origin; four.Y += extends.Y;

 FVector five = one; five.Z += extends.Z;
 FVector six = two; six.Z += extends.Z;
 FVector seven = tree; seven.Z += extends.Z;
 FVector eight = four; eight.Z += extends.Z;

    FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    if (W2S2(one, &s1) && W2S2(two, &s2) && W2S2(tree, &s3) && W2S2(four, &s4) &&
    W2S2(five, &s5) && W2S2(six, &s6) && W2S2(seven, &s7) && W2S2(eight, &s8))
    {
        
    Line(HUD,s1, s2, Color);
    Line(HUD,s2, s3, Color);
    Line(HUD,s3, s4, Color);
    Line(HUD,s4, s1, Color);
 
    Line(HUD,s5, s6, Color);
    Line(HUD,s6, s7, Color);
    Line(HUD,s7, s8, Color);
    Line(HUD,s8, s5, Color);
 
    Line(HUD,s1, s5, Color);
    Line(HUD,s2, s6, Color);
    Line(HUD,s3, s7, Color);
    Line(HUD,s4, s8, Color);

}
}
void DrawCircle(AHUD *HUD, int x, int y, int radius, int numsides, FLinearColor OutlineColor)
{
	UCanvas *Canvas = HUD->Canvas;
	float Step = M_PI * 2.0 / numsides;
	int Count = 0;
	FVector2D V[128];
	for (float a = 0; a < M_PI * 2.0; a += Step)
	{
		float screenWidth = radius * cos(a) + x;
		float Y1 = radius * sin(a) + y;
		float X2 = radius * cos(a + Step) + x;
		float Y2 = radius * sin(a + Step) + y;
		V[Count].X = screenWidth;
		V[Count].Y = Y1;
		V[Count + 1].X = X2;
		V[Count + 1].Y = Y2;
		Canvas->K2_DrawLine(FVector2D({V[Count].X, V[Count].Y}), FVector2D({X2, Y2}), 1.f, OutlineColor);
	}
}
void LineE(ImDrawList *draw, Vector3 posFrom, Vector3 posTo, float Thickness, ImColor col) {
 draw->AddLine({posFrom.X, posFrom.Y},{posTo.X, posTo.Y},col, 2.0f);
}
void DrawArrowsFilled(ImDrawList * draw, Vector3 xy1, Vector3 xy2, Vector3 xy3,Vector3 xy4, Vector3 xy5 , Vector3 xy6 , Vector3 xy7, float Thickness, ImColor col) {
LineE(draw,xy1, xy2, Thickness,col);
LineE(draw,xy2, xy3, Thickness,col);
LineE(draw,xy3, xy7, Thickness,col);
LineE(draw,xy7, xy6, Thickness,col);
LineE(draw,xy6, xy5, Thickness,col);
LineE(draw,xy5, xy4, Thickness,col);
LineE(draw,xy4, xy1, Thickness,col);
}
void DrawOutlinedText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, FLinearColor OutlineColor, bool isCenter = false)
{
	UCanvas *DebugCanvas = HUD->DebugCanvas;
	DebugCanvas->K2_DrawText(tslFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, true, OutlineColor);
}
void RotateTriangle(std::array<Vector3, 3> & points, float rotation) {
const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
for (auto & point : points) {
point = point - points_center;
const auto temp_x = point.X;
const auto temp_y = point.Y;
const auto theta = DEG2RAD(rotation);
const auto c = cosf(theta);
const auto s = sinf(theta);
point.X = temp_x * c - temp_y * s;
point.Y = temp_x * s + temp_y * c;
point = point + points_center;}}
void DrawText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, bool isCenter = false)
{
	UCanvas *DebugCanvas = HUD->DebugCanvas;
	DebugCanvas->K2_DrawText(tslFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, false, {});
}

void DrawSmallOutlinedText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, FLinearColor OutlineColor, bool isCenter = false)
{
	UCanvas *DebugCanvas = HUD->DebugCanvas;
	DebugCanvas->K2_DrawText(robotoTinyFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, true, OutlineColor);
}

void DrawSmallText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, bool isCenter = false)
{
	UCanvas *DebugCanvas = HUD->DebugCanvas;
	DebugCanvas->K2_DrawText(robotoTinyFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, false, {});
}

static void DrawArrowsSansero(AHUD *hud, std::array<FVector2D, 7> Loc, float thickness, FLinearColor color) {
    for (int i = 10; i < 25; i++) {
        DrawLine(hud, Loc.at(i), Loc.at(7), thickness, color);
    }
    for (int i = 26; i < 38; i++) {
        DrawLine(hud, Loc.at(i), Loc.at(7), thickness + 1.5, color);
        DrawLine(hud, Loc.at(i), Loc.at(8), thickness + 1.5f, color);
        DrawLine(hud, Loc.at(i), Loc.at(9), thickness + 1.5f, color);
    }
}

void *LoadFont(void *)
{
	while (!tslFont || !robotoTinyFont)
	{
		tslFont = UObject::FindObject<UFont>("Font Roboto.Roboto");
		robotoTinyFont = UObject::FindObject<UFont>("Font RobotoDistanceField.RobotoDistanceField");
		sleep(1);
	}
	return 0;
}


void RenderESPPRIVATE(AHUD *HUD, int ScreenWidth, int ScreenHeight) {

HOOK_LIB_NO_ORIG("libUE4.so", "0x5D119D8", sub_5D119D8);
PATCH_LIB("libgcloud.so","0x3CF53C", "FD 03 00 91");
PATCH_LIB("libgcloud.so","0x3CF544", "F3 03 00 AA");
PATCH_LIB("libgcloud.so","0x3CF564", "80 03 80 D2");
PATCH_LIB("libgcloud.so","0x40F928", "C0 0C 80 52");
PATCH_LIB("libgcloud.so","0x40F938", "E0 03 13 AA");
PATCH_LIB("libgcloud.so","0x40F940", "E1 03 03 AA");
PATCH_LIB("libgcloud.so","0x21F92C", "E2 03 00 AA");
PATCH_LIB("libgcloud.so","0x21F94C", "20 00 80 52");
PATCH_LIB("libgcloud.so","0x978C8", "F4 03 00 AA");
PATCH_LIB("libgcloud.so","0x978F0", "E0 03 19 AA");
PATCH_LIB("libgcloud.so","0x5EB540", "90 56 61 00");
PATCH_LIB("libgcloud.so","0x4A149E", "52 65 63 6F 6E 6E 65 63 74 53");
PATCH_LIB("libanogs.so","0x3FB828", "00 E4 00 6F");
PATCH_LIB("libanogs.so","0x3FB848", "E0 03 01 AA");
PATCH_LIB("libanogs.so","0x3FB84C", "E1 03 08 AA");
PATCH_LIB("libanogs.so","0x3FB858", "F4 03 00 AA");
PATCH_LIB("libanogs.so","0x3FB85C", "21 00 80 52");
PATCH_LIB("libanogs.so","0x3FB860", "02 10 80 52");
PATCH_LIB("libanogs.so","0x3FB864", "E0 03 13 AA");
PATCH_LIB("libanogs.so","0x3FB874", "E0 03 14 AA");
PATCH_LIB("libanogs.so","0x109884", "F3 03 00 AA");
PATCH_LIB("libanogs.so","0x10988C", "F4 03 00 2A");
PATCH_LIB("libanogs.so","0x109890", "E0 03 13 AA");
PATCH_LIB("libanogs.so","0x1098A0", "E0 03 00 AA");
PATCH_LIB("libanogs.so","0x425818", "F6 03 04 2A");
PATCH_LIB("libanogs.so","0x42581C", "F5 03 03 2A");
PATCH_LIB("libanogs.so","0x425820", "F4 03 02 AA");
PATCH_LIB("libanogs.so","0x425824", "F3 03 01 AA");
PATCH_LIB("libanogs.so","0x425828", "F7 03 00 AA");
PATCH_LIB("libanogs.so","0x3C1860", "00 07 80 52");
PATCH_LIB("libanogs.so","0x3C1864", "61 0C 80 12");
PATCH_LIB("libanogs.so","0x3C1868", "E2 03 15 AA");
PATCH_LIB("libanogs.so","0x3C186C", "E3 03 14 2A");
PATCH_LIB("libanogs.so","0x3C1870", "E4 03 13 2A");
PATCH_LIB("libanogs.so","0x2A1830", "08 00 80 D2");

PATCH_LIB("libanogs.so","0x442C1F"," 43 53 52 65 63 6F 6E 6E 65 63");//offline fix
PATCH_LIB("libanogs.so","0x466DB7"," 63 6D 64 00");//flah ban fix

PATCH_LIB("libanogs.so", "0xDF2FC", "00 00 80 D2 C0 03 5F D6");//Crash fix

//MAKE BY @MODAMELLA
  updateSkin();
        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localPlayerController = 0;
int totalEnemies = 0, totalBots = 0;
auto GWorld = GetWorld();
    if (GWorld) {
   
    auto Actors = *(TArray<AActor *> *) ((uintptr_t) GWorld->PersistentLevel + Actors_Offset);

        UCanvas *Canvas = HUD->Canvas;
        if (Canvas) {
auto localPlayer = g_LocalPlayer;
        auto localController = g_LocalController;
	    
static bool loadFont = false;
        if (!loadFont) {
            pthread_t t;
            pthread_create(&t, 0, LoadFont, 0);
            loadFont = true;
        }

                if (!tslFont || !robotoTinyFont)
            return;
	UGameplayStatics *gGameplayStatics = (UGameplayStatics *) UGameplayStatics::StaticClass();
            auto GWorld = GetWorld();
            if (GWorld) {
                UNetDriver *NetDriver = GWorld->NetDriver;
                if (NetDriver) {
                    UNetConnection *ServerConnection = NetDriver->ServerConnection;
                    if (ServerConnection) {
                        localPlayerController = (ASTExtraPlayerController *) ServerConnection->PlayerController;
                    }
                }

                if (localPlayerController) {
                     
                    std::vector<ASTExtraPlayerCharacter *> PlayerCharacter;
                    GetAllActors(PlayerCharacter);
                    for (auto actor = PlayerCharacter.begin();
                         actor != PlayerCharacter.end(); actor++) {
                        auto Actor = *actor;

                        if (Actor->PlayerKey ==
                            ((ASTExtraPlayerController *) localPlayerController)->PlayerKey) {
                            localPlayer = Actor;
                            break;
                        }
                    }

                    {
						
						if (localPlayer) {
							
	
if (ModSkinn){
								
								if (ModSkinn){
                              int pController = 982;
                                        auto VTable = (void **) g_LocalController->VTable;
                                        auto f_mprotect = [](uintptr_t addr, size_t len,
                                                             int32_t prot) -> int32_t {
                                            static_assert(PAGE_SIZE == 4096);
                                            constexpr
                                            size_t page_size = static_cast<size_t>(PAGE_SIZE);
                                            void *start = reinterpret_cast<void *>(addr &
                                                                                   -page_size);
                                            uintptr_t end =
                                                    (addr + len + page_size - 20) & -page_size;
                                            return mprotect(start, end -
                                                                   reinterpret_cast<uintptr_t>(start),
                                                            prot);
                                        };
                                        if (VTable && (VTable[pController] != hk_Broadcast)) {
                                            orig_Broadcast = decltype(orig_Broadcast)(
                                                    VTable[pController]);

                                            f_mprotect((uintptr_t)(&VTable[pController]),
                                                       sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                            VTable[pController] = (void *) hk_Broadcast;
                                        }
									}
		
	 if (localPlayer->WeaponManagerComponent != 0) {
     if (localPlayer->WeaponManagerComponent->CurrentWeaponReplicated != 0 ) {
         int weapowep = localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponID();
		auto currentTime = std::chrono::steady_clock::now();
         auto landchud = localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->synData;
         auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastWeaponChangeTime).count();
         if (timeDiff > 1000) {
         for (int j = 0; j < landchud.Num(); j++) {
             auto& weaponInfo = landchud[j];
             auto weaponid = weaponInfo.DefineID.TypeSpecificID;
             if (weaponid != 0)
             {
				 if (preferences.AKM && weapowep == 101001){
				 for (int i = 0; i < sizeof(akmv) / sizeof(akmv[0]); i++) {
                 if (weaponid == akmv[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.AKM;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(akmmag) / sizeof(akmmag[0]); i++) {
                 if (weaponid == akmmag[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.AKM_Mag;
                     break;
                  }
				 }
				}
				if (preferences.KAR98 && weapowep == 103001){
				 for (int i = 0; i < sizeof(kar) / sizeof(kar[0]); i++) {
                 if (weaponid == kar[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.K98;
                     break;
                  }
				 }
				}
				if (preferences.M24 && weapowep == 103002){
				 for (int i = 0; i < sizeof(m24) / sizeof(m24[0]); i++) {
                 if (weaponid == m24[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M24;
                     break;
                  }
				 }
				}
				if (preferences.AWM && weapowep == 103003){
				 for (int i = 0; i < sizeof(awm) / sizeof(awm[0]); i++) {
                 if (weaponid == awm[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.AWM;
                     break;
                  }
				 }
				}
				
				
				if (preferences.TOMMY && weapowep == 102004){
				 for (int i = 0; i < sizeof(tommy) / sizeof(tommy[0]); i++) {
                 if (weaponid == tommy[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Thompson;
                     break;
                  }
				 }
				}
				if (preferences.ACE32 && weapowep == 101102){
				 for (int i = 0; i < sizeof(ace32) / sizeof(ace32[0]); i++) {
                 if (weaponid == ace32[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.ACE32;
                     break;
                  }
				 }
				}
				
				if (preferences.BIZON && weapowep == 102005){
				 for (int i = 0; i < sizeof(bizon) / sizeof(bizon[0]); i++) {
                 if (weaponid == bizon[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Bizon;
                     break;
                  }
				 }
				}
				
				if (preferences.VECTOR && weapowep == 102003){
				 for (int i = 0; i < sizeof(vector) / sizeof(vector[0]); i++) {
                 if (weaponid == vector[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Vector;
                     break;
                  }
				 }
				}
				if (preferences.UMP && weapowep == 102002){
				 for (int i = 0; i < sizeof(ump) / sizeof(ump[0]); i++) {
                 if (weaponid == ump[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.UMP;
                     break;
                  }
				 }
				}
				if (preferences.UZI && weapowep == 102001){
				 for (int i = 0; i < sizeof(uzi) / sizeof(uzi[0]); i++) {
                 if (weaponid == uzi[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.UZI;
                     break;
                  }
				 }
				}
				if (preferences.M16 && weapowep == 101002){
				 for (int i = 0; i < sizeof(m16) / sizeof(m16[0]); i++) {
                 if (weaponid == m16[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M16A4;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m16s) / sizeof(m16s[0]); i++) {
                 if (weaponid == m16s[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M16A4_Stock;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m16mag) / sizeof(m16mag[0]); i++) {
                 if (weaponid == m16mag[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M16A4_Mag;
                     break;
                  }
				 }
				}
				if (preferences.PAN && weapowep == 108004){
				 for (int i = 0; i < sizeof(pan) / sizeof(pan[0]); i++) {
                 if (weaponid == pan[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Pan;
                     break;
                  }
				 }
				}
				if (preferences.AUG && weapowep == 101006){
				 for (int i = 0; i < sizeof(aug) / sizeof(aug[0]); i++) {
                 if (weaponid == aug[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.AUG;
                     break;
                  }
				 }
				}
				if (preferences.GROZA && weapowep == 101005){
				 for (int i = 0; i < sizeof(groza) / sizeof(groza[0]); i++) {
                 if (weaponid == groza[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Groza;
                     break;
                  }
				 }
				}
				if (preferences.DP28 && weapowep == 105002){
				 for (int i = 0; i < sizeof(dp) / sizeof(dp[0]); i++) {
                 if (weaponid == dp[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.DP28;
                     break;
                  }
				 }
				}
				if (preferences.M249 && weapowep == 105001){
				 for (int i = 0; i < sizeof(m249) / sizeof(m249[0]); i++) {
                 if (weaponid == m249[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M249;
                     break;
                  }
				 }
				}
				
				if (preferences.SCARL && weapowep == 101003){
				 for (int i = 0; i < sizeof(scar) / sizeof(scar[0]); i++) {
                 if (weaponid == scar[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Scar;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(scarmag) / sizeof(scarmag[0]); i++) {
                 if (weaponid == scarmag[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.Scar_Mag;
                     break;
                  }
				 }
				}
				
				if (preferences.M762 && weapowep == 101008){
				 for (int i = 0; i < sizeof(m7) / sizeof(m7[0]); i++) {
                 if (weaponid == m7[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M762;
                     
                     if (Luminous == 1) {
                     weaponInfo.DefineID.TypeSpecificID = 1101008136;
                   
                     }
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m7mag) / sizeof(m7mag[0]); i++) {
                 if (weaponid == m7mag[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M762_Mag;
                     break;
                  }
				 }
				}
		
				if (preferences.M416 && weapowep == 101004){
				 for (int i = 0; i < sizeof(m4v) / sizeof(m4v[0]); i++) {
                 if (weaponid == m4v[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M416_1 ;
                     break;
                  }
				 }
				 
				 for (int i = 0; i < sizeof(m4mag) / sizeof(m4mag[0]); i++) {
                 if (weaponid == m4mag[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M416_2;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m4sight) / sizeof(m4sight[0]); i++) {
                 if (weaponid == m4sight[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M416_3;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m4stock) / sizeof(m4stock[0]); i++) {
                 if (weaponid == m4stock[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M416_4;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m4stock1) / sizeof(m4stock1[0]); i++) {
                 if (weaponid == m4stock1[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M416_stock;
                     break;
                  }
				 }
				 for (int i = 0; i < sizeof(m4reddot) / sizeof(m4reddot[0]); i++) {
                 if (weaponid == m4reddot[i]) {
                     weaponInfo.DefineID.TypeSpecificID = new_Skin.M416_reddot;
                     break;
                  }
				 }
				}
                 localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->DelayHandleAvatarMeshChanged();
                 lastWeaponChangeTime = currentTime;
             }
         }
     }
 }
}


if (localPlayer -> CurrentVehicle) {
        if (localPlayer -> CurrentVehicle -> VehicleAvatar) {
          std::string SkinIDStr = std::to_string((int) localPlayer -> CurrentVehicle -> VehicleAvatar -> GetDefaultAvatarID());
          Active::SkinCarDefault = localPlayer -> CurrentVehicle -> GetAvatarID();

		  
          if (preferences.Moto && strstr(SkinIDStr.c_str(), "1901")) {
            Active::SkinCarMod = new_Skin.Moto;
            Active::SkinCarNew = true;
          } else if (preferences.Dacia && strstr(SkinIDStr.c_str(), "1903")) {
            Active::SkinCarMod = new_Skin.Dacia;
            Active::SkinCarNew = true;
          } else if (preferences.Boat && strstr(SkinIDStr.c_str(), "1911")) {
            Active::SkinCarMod = new_Skin.Boat;
            Active::SkinCarNew = true;
          } else if (preferences.MiniBus && strstr(SkinIDStr.c_str(), "1904")) {
            Active::SkinCarMod = new_Skin.MiniBus;
            Active::SkinCarNew = true;
          } else if (preferences.Mirado && strstr(SkinIDStr.c_str(), "1914")) {
            Active::SkinCarMod = new_Skin.Mirado;
            Active::SkinCarNew = true;
          } else if (preferences.Mirado && strstr(SkinIDStr.c_str(), "1915")) {
            Active::SkinCarMod = new_Skin.Mirado;
            Active::SkinCarNew = true;
          } else if (preferences.Buggy && strstr(SkinIDStr.c_str(), "1907")) {
            Active::SkinCarMod = new_Skin.Buggy;
            Active::SkinCarNew = true;
          }else if (preferences.CoupeRB && strstr(SkinIDStr.c_str(), "1961")) {
            Active::SkinCarMod = new_Skin.CoupeRP;
            Active::SkinCarNew = true;
          } else if (preferences.BigFoot && strstr(SkinIDStr.c_str(), "1953")) {
            Active::SkinCarMod = new_Skin.Bigfoot;
            Active::SkinCarNew = true;
          } else if (preferences.UAZ && strstr(SkinIDStr.c_str(), "1908")) {
            Active::SkinCarMod = new_Skin.UAZ;
            Active::SkinCarNew = true;
          } else Active::SkinCarNew = false;

          if (Active::SkinCarDefault != Active::SkinCarMod && Active::SkinCarNew) {
            
            localPlayer -> CurrentVehicle -> VehicleAvatar -> ChangeItemAvatar(Active::SkinCarMod, true);
          }
        }
      }

	  if (localPlayerController->BackpackComponent){
	 auto data = localPlayerController->BackpackComponent->ItemListNet;
	 auto bag = data.IncArray;
	 for (int j = 0; j < bag.Num(); j++) {
	 int ID = bag[j].Unit.DefineID.TypeSpecificID;
	  
	  if (preferences.Bagg){
for (int i = 0; i < sizeof(Bag) / sizeof(Bag[0]); i++) {
                 if (ID == Bag[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = bag3;
                     if (Luminous == 1) {
                     bag[j].Unit.DefineID.TypeSpecificID = 1501003571;
                     
                     }
                     if (Luminous == 2){ //Bape
                     bag[j].Unit.DefineID.TypeSpecificID = 1501003058;
                     }
                     if (Luminous == 3){ //Inv
                     bag[j].Unit.DefineID.TypeSpecificID = 1501003220;
                     }
                     if (Luminous == 4){ //Pr
                     bag[j].Unit.DefineID.TypeSpecificID = 1501003174;
                     }
                     break;
                 }}}}}
				if (localPlayer -> AvatarComponent2) {

        auto AvatarComp = localPlayer -> AvatarComponent2;
		
        FNetAvatarSyncData NetAvatarComp = * (FNetAvatarSyncData * )((uintptr_t) AvatarComp + 0x388);
        auto Slotsybc = NetAvatarComp.SlotSyncData;
				if (preferences.Bagg){
		Slotsybc[8].ItemId = bag3;
		}
		localPlayer->AvatarComponent2->OnRep_BodySlotStateChanged();
		}
 if (localPlayerController->BackpackComponent){
	 auto data = localPlayerController->BackpackComponent->ItemListNet;
	 auto bag = data.IncArray;
	 for (int j = 0; j < bag.Num(); j++) {
	 int ID = bag[j].Unit.DefineID.TypeSpecificID;
	 
				
				if (preferences.Outfit){
 for (int i = 0; i < sizeof(SuitX) / sizeof(SuitX[0]); i++) {
                 if (ID == SuitX[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = new_Skin.XSuits;
                     break;
                  }
				 }
				}
				if (preferences.Helmett){
for (int i = 0; i < sizeof(Helmet) / sizeof(Helmet[0]); i++) {
                 if (ID == Helmet[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = helmett3;
                     break;
                  }
				 }
				}
				if (preferences.Emote){
for (int i = 0; i < sizeof(emote1) / sizeof(emote1[0]); i++) {
                 if (ID == emote1[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = sEmote1;
                     break;
                  }
				 }
for (int i = 0; i < sizeof(emote2) / sizeof(emote2[0]); i++) {
                 if (ID == emote2[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = sEmote2;
                     break;
                  }
				 }
for (int i = 0; i < sizeof(emote3) / sizeof(emote3[0]); i++) {
                 if (ID == emote3[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = sEmote3;
                     break;
                  }
				 }
				}
				if (preferences.PAN){
				 for (int i = 0; i < sizeof(pan) / sizeof(pan[0]); i++) {
                 if (ID == pan[i]) {
                     bag[j].Unit.DefineID.TypeSpecificID = new_Skin.Pan;
                     break;
                    }
				  }
				}
            }
        }

 
 if (localPlayer -> AvatarComponent2) {

        auto AvatarComp = localPlayer -> AvatarComponent2;
		
        FNetAvatarSyncData NetAvatarComp = * (FNetAvatarSyncData * )((uintptr_t) AvatarComp + 0x388);
        auto Slotsybc = NetAvatarComp.SlotSyncData;
		if (preferences.Parachute){
        Slotsybc[11].ItemId = new_Skin.Parachute;
		}
		if (preferences.Outfit){
		Slotsybc[5].ItemId = new_Skin.XSuits;
		Slotsybc[4].ItemId = new_Skin.XSuits;
		if (preferences.Config.Skin.XSuits == 26){
Slotsybc[6].ItemId = new_Skin.XSuits;
Slotsybc[7].ItemId = new_Skin.XSuits;
}
if (Luminous == 2){ //Bape
Slotsybc[5].ItemId = 1404049;
Slotsybc[6].ItemId = 1404050;
Slotsybc[7].ItemId = 1404051;
}
if (Luminous == 1) {
Slotsybc[5].ItemId = 1407225;
}
if (Luminous == 3){ //Inv
Slotsybc[4].ItemId = 1403010;
Slotsybc[5].ItemId = 1405145;
Slotsybc[9].ItemId = 1502003014;
}
if (Luminous == 4){ //Pr
Slotsybc[5].ItemId = 1406469;
Slotsybc[9].ItemId = 1502003014;
}
Slotsybc[9].ItemId = helmett3;
		
	
		
		Slotsybc[8].ItemId = bag3;
		}
		
		 
		
		
		
  auto now = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

if (elapsed < 100 && callFunction) {
    localPlayer->AvatarComponent2->OnRep_BodySlotStateChanged();
} else {
    callFunction = false;
}}
}
    }
	screen_Width = ScreenWidth;
    screen_Height = ScreenHeight;
	
	
	
	tslFont->LegacyFontSize = 20;
	if (Config.HandCam) {
        out = false;
    } else {
        out = true;
    }
     if (out) {
        DrawOutlinedText(HUD, FString("Reohecks"), {(float) screen_Width / 2, 40}, COLOR_WHITE, COLOR_BLACK, true);
        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
}
		for (int i = 0; i < Actors.Num(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *) Actor;
                break;
            }
        }
        
        if (localController) {
            for (int i = 0; i < Actors.Num(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey ==
                        localController->PlayerKey) {
                        localPlayer = (ASTExtraPlayerCharacter *) Actor;
                        break;
                    }
                }
            }


            if (localPlayer) {
                if (localPlayer->PartHitComponent) {
                    auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                    for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                        ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                    }
                    localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                }
                					  if (Config.HighRisk.Ipad){
                                localPlayer->ThirdPersonCameraComponent->SetFieldOfView(Config.IpadS);
                                }
					  
					  
    if (Config.AimBot.Enable) {
                    ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
                    if (Target) {
                        bool triggerOk = false;
                        if (Config.AimBot.Trigger != EAimTrigger::None) {
                            if (Config.AimBot.Trigger == EAimTrigger::Shooting) {
                                triggerOk = localPlayer->bIsWeaponFiring;
                            } else if (Config.AimBot.Trigger == EAimTrigger::Scoping) {
                                triggerOk = localPlayer->bIsGunADS;
                            } else if (Config.AimBot.Trigger == EAimTrigger::Both) {
                                triggerOk = localPlayer->bIsWeaponFiring && localPlayer->bIsGunADS;
                            } else if (Config.AimBot.Trigger == EAimTrigger::Any) {
                                triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
                            }
                        } else triggerOk = true;
                        if (triggerOk){
                    FVector targetAimPos = Target->GetBonePos("Head", {});
                    if (Config.AimBot.Target == EAimTarget::Chest){
                        targetAimPos.Z -= 29.55f;
                    targetAimPos.Y -= 1.224f;}
                    
                            auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                            if (WeaponManagerComponent) {
                                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                if ((int) propSlot.GetValue() >= 1 &&
                                    (int) propSlot.GetValue() <= 3) {
                                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                    if (CurrentWeaponReplicated) {
                                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                        if (ShootWeaponComponent) {
                                            UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                            if (ShootWeaponEntityComponent) {
                                                ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                                                if (CurrentVehicle) {
                                                    FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;
                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    LinearVelocity, timeToTravel));
                                                } else {
                                                    FVector Velocity = Target->GetVelocity();
                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;
                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    Velocity, timeToTravel));}
                            if (Config.AimBot.Recoil) {
        if (g_LocalPlayer->bIsGunADS) {
        if (g_LocalPlayer->bIsWeaponFiring) {
        float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;                                                                                 
        targetAimPos.Z -= dist * Config.AimBot.Recc;}}}
        
                                                
                                            FVector fDir = UKismetMathLibrary::Subtract_VectorVector(targetAimPos, g_LocalController->PlayerCameraManager->CameraCache.POV.Location);
                                            FRotator Yaptr = UKismetMathLibrary::Conv_VectorToRotator(fDir);
                                            FRotator CpYaT = localController->PlayerCameraManager->CameraCache.POV.Rotation;
                                            Yaptr.Pitch -= CpYaT.Pitch;
                                            Yaptr.Yaw -= CpYaT.Yaw;
                                            Yaptr.Roll = 0.f;
                                            IMGUI_GOD(Yaptr);
                                            CpYaT.Pitch += Yaptr.Pitch / AimSmooth; 
                                            CpYaT.Yaw += Yaptr.Yaw / AimSmooth; 
                                            CpYaT.Roll = 0.f;
                                            localController->SetControlRotation(CpYaT,"");
                                            }}}}}}}}            
                                         
if (Config.HandCam) {
        out = false;
    } else {
        out = true;
    }
     if (out) {
                    for (int i = 0; i < Actors.Num(); i++) {
                    auto Actor = Actors[i];
                    if (isObjectInvalid(Actor))
                         continue;
                    auto Player = (ASTExtraPlayerCharacter *) Actor;
                    FLinearColor  PLAYERSPONG = FLinearColor(0, 255, 0, 50);
                   FLinearColor  Kmkl001 = FLinearColor(74, 232, 145, 255);
                   FLinearColor  Kmkl002 = FLinearColor(232, 76, 65, 255);
                   
                    FLinearColor  PLAYERSPONGG = FLinearColor(1.f, 0, 0, 1.f);
                    float Distance = Player->GetDistanceTo(localPlayer) / 100.f;
                    if (Distance < 500.f) {
                    if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    auto Player = (ASTExtraPlayerCharacter *) Actor;
                    if (Player->PlayerKey == localController->PlayerKey)
                        continue;

                    if (Player->TeamID == localController->TeamID)
                        continue;

                    if (Player->bDead)
                        continue;

                    if (!Player->RootComponent)
                        continue;

                    if (Config.NoBot)
                        if (Player->bEnsure)
                            continue;

                            if (Player->bEnsure)
                                totalBots++;
                            else totalEnemies++;

                            FVector Head = GetBoneLocationByName(Player, "Head");
                            Head.Z += 12.5f;

                            FVector Root = GetBoneLocationByName(Player, "Root");
                                FVector2D HeadSc, RootSc;
                                if (GetGameplayStatics()->ProjectWorldToScreen(localController, Head, false, &HeadSc) && GetGameplayStatics()->ProjectWorldToScreen(localController, Root, false, &RootSc)) {
                                            
		
									
									                                            if (Config.Linee) {
                                                bool IsVisible = localController->LineOfSightTo(Player, {0,0,0}, true);
                                                if (IsVisible)
                                                DrawLine(HUD, {static_cast<float>(ScreenWidth / 2), 0}, HeadSc, 1.5f, COLOR_GREEN);
                                                else
                                                DrawLine(HUD, {static_cast<float>(ScreenWidth / 2), 0}, HeadSc, 1.5f, COLOR_WHITE);
                                                }
												
												
												

												
												
									
		 if (Config.Asp.Box) {
                                                bool IsVisible = localController->LineOfSightTo(Player, {0,0,0}, true);
                                                FVector BoxSize;
                                                BoxSize.X = 100.f; // Height
                                                BoxSize.Y = 100.f; // Front
                                                BoxSize.Z = 180.f; // Height
                                                if (IsVisible)
                                                Box3D(HUD, Player->K2_GetActorLocation(), BoxSize, COLOR_GREEN);
                                                else
                                                Box3D(HUD, Player->K2_GetActorLocation(), BoxSize, COLOR_WHITE);
                                            }
	
	   
						      
       
					
                                          		
											if (Config.Asp.Skeleton) {
                                                
                                                static std::vector<std::string> right_arm{"neck_01", "clavicle_r", "upperarm_r", "lowerarm_r", "hand_r", "item_r"};
                                                static std::vector<std::string> left_arm{"neck_01", "clavicle_l", "upperarm_l", "lowerarm_l", "hand_l", "item_l"};
                                                static std::vector<std::string> spine{"Head", "neck_01", "spine_03", "spine_02", "spine_01", "Pelvis"};
                                                static std::vector<std::string> lower_right{"Pelvis", "thigh_r", "calf_r", "foot_r"};
                                                static std::vector<std::string> lower_left{"Pelvis", "thigh_l", "calf_l", "foot_l"};
                                                static std::vector<std::vector<std::string>> skeleton{right_arm, left_arm, spine, lower_right, lower_left};

                                                FHitResult HitResult;
                                                bool IsVisible = localController->LineOfSightTo(Player, {0,0,0}, true);
                                                 for (auto &boneStructure : skeleton) {
                                                    std::string lastBone;
                                                    for (std::string &currentBone : boneStructure) {
                                                        if (!lastBone.empty()) {
                                                            FVector wBoneFrom = GetBoneLocationByName(Player, lastBone.c_str());
                                                            FVector wBoneTo = GetBoneLocationByName(Player, currentBone.c_str());
                                                            FVector2D boneFrom, boneTo;

                                                            if (UGameplayStatics::ProjectWorldToScreen(localController, wBoneFrom, false, &boneFrom) && UGameplayStatics::ProjectWorldToScreen(localController, wBoneTo, false, &boneTo)) {
                                                                if (IsVisible)
                                                                    DrawLine(HUD, boneFrom, boneTo, 1.5f, COLOR_GREEN);
                                                                else
                                                                    DrawLine(HUD, boneFrom, boneTo, 1.5f, COLOR_WHITE);
                                                            }
                                                        }
                                                        lastBone = currentBone;
                                                    }
                                                }
                                            }                                
											 
											
											    if(Config.Asp.Health){
                                        float CurHP = std::max(0.f, std::min(Player->Health, Player->HealthMax));
                                float MaxHP = Player->HealthMax;
                                FLinearColor ColorHP = {std::min(((510.f * (MaxHP - CurHP)) / MaxHP) / 255.f, 1.f), std::min(((510.f * CurHP) / MaxHP) / 255.f, 1.f), 0.f, 0.5f};
                                if (CurHP == 0 && !Player->bDead) {
                                    ColorHP = {1.f, 1.f, 0, 1.f};
                                    CurHP = Player->NearDeathBreath;
                                    USTCharacterNearDeathComp *NearDeatchComponent = Player->NearDeatchComponent;
                                    if (NearDeatchComponent) {
                                        MaxHP = NearDeatchComponent->BreathMax;
                                    }
                                }
                                auto AboveHead = Player->GetHeadLocation(true);
                                AboveHead.Z += 36.f;
                                FVector2D AboveHeadSc;
                                if (gGameplayStatics->ProjectWorldToScreen(localController, AboveHead, false, &AboveHeadSc)) {
                                    auto mWidthScale = std::min(0.0f * 100.0f, 0.0f);
                                /*    auto mWidth2 = 10.0f - mWidthScale;
                                    auto mWidth3 = 20.0f - mWidthScale;
                                    auto mWidth4 = 30.0f - mWidthScale;
                                    auto mWidth5 = 40.0f - mWidthScale;*/
                                    auto mWidth = 100.0f - mWidthScale;
                                    auto mHeight = mWidth * 0.150f;
                                    AboveHeadSc.X -= (mWidth / 2);
                                    AboveHeadSc.Y -= (mHeight * 0.5f);
                                       if (Player->bEnsure) {       
                                    DrawFilledRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, (CurHP * mWidth / MaxHP), mHeight, COLOR_LIME);
                                                                                   } else {
                                    DrawFilledRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, (CurHP * mWidth / MaxHP), mHeight, COLOR_RED);
                                    }
                                    //血量绘图
                               /*     DrawRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, mWidth2, mHeight, 1.0f, {0, 0, 0, 1.f});
                                    DrawRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, mWidth3, mHeight, 1.0f, {0, 0, 0, 1.f});
                                    DrawRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, mWidth4, mHeight, 1.0f, {0, 0, 0, 1.f});
                                    DrawRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, mWidth5, mHeight, 1.0f, {0, 0, 0, 1.f});*/
                                    DrawRectangle(HUD, {AboveHeadSc.X, AboveHeadSc.Y - 7}, mWidth, mHeight, 1.0f, {0, 0, 0, 1.f});
                                }
                                        }
										
										  if (Config.Asp.TeamID | Config.Asp.Distance) {
                                            auto AboveHead = Player->GetHeadLocation(true);
                                AboveHead.Z += 36.f;
                                FVector2D AboveHeadSc;
                                if (gGameplayStatics->ProjectWorldToScreen(localController, AboveHead, false, &AboveHeadSc)) {
                                    std::wstring ws;
                             if (Config.Asp.TeamID) {
                             ws += L" ID :";
                                    ws = std::to_wstring(Player->TeamID);
                                    ws += L"  |  ";
                                    }
                               if (Config.Asp.Distance) {
                                    ws += std::to_wstring((int) Distance);
                                    ws += L" M";
                                    }
                                    auto mWidthScale = std::min(0.006f * Distance, 100.f);
                                    auto mWidth = 20.f - mWidthScale;
                                    auto mHeight = mWidth * 0.125f;
                                    AboveHeadSc.X -= (mWidth / 0);
                                    AboveHeadSc.Y -= (mHeight * 10.0f);
                                    tslFont->LegacyFontSize = fmax(5.5f, 10.5f - (int)(Distance / 100));
                                    DrawOutlinedText(HUD, FString(ws), {HeadSc.X - 9, AboveHeadSc.Y - 7.0},  COLOR_GREEN, COLOR_BLACK, true);
                                }
                            }

                                                                                if (Config.Asp.Name) {
                                                                                
                                                                                                             auto AboveHead = Player->GetHeadLocation(true);
                                AboveHead.Z += 36.f;
                                FVector2D AboveHeadSc;
                                if (gGameplayStatics->ProjectWorldToScreen(localController, AboveHead, false, &AboveHeadSc)) {
                                    std::wstring ws;
                                    if (Config.Asp.Name) {
                                     //  ws = std::to_wstring(Player->TeamID);
                                        auto playername = Player->PlayerName;
                                        if (Player->bEnsure) {
                                           // ws += L" ";
                                            ws += L"Bot";
                                        } else {
                                           // ws += L" ";
                                            ws += playername.ToWString();
                                        }
                                    }

                                    auto mWidthScale = std::min(0.006f * Distance, 100.f);
                                    auto mWidth = 20.f - mWidthScale;
                                    auto mHeight = mWidth * 0.125f;
                                    AboveHeadSc.X -= (mWidth / 2);
                                    AboveHeadSc.Y -= (mHeight * 1.5f);
                                    tslFont->LegacyFontSize = fmax(3.5f, 7.5f  - (int)(Distance / 100));
                                    DrawOutlinedText(HUD, FString(ws), {HeadSc.X - 7, AboveHeadSc.Y - 5.0},  COLOR_YELLOW, COLOR_BLACK, true);

                                        
                                    }
							}
											
											
											if (Config.Asp.Genn) {
                             if (Actor->IsA(ASTExtraGrenadeBase::StaticClass())) {
                                auto Genn = (ASTExtraGrenadeBase *) Actor;
                               auto resa = getObjectPath(Genn);
                                if (strstr(resa, "BP_Grenade_Shoulei_C")){
                            if (!Genn->RootComponent)
                                continue;
                         float Distance = Genn->GetDistanceTo(localPlayer) / 100.f;
                             FVector2D GrenadePos;
                            if (UGameplayStatics::ProjectWorldToScreen(localController, Genn->RootComponent->RelativeLocation, false, &GrenadePos)) {
                                       std::string s;
                                       s += "Grenade -";
                                       s += std::to_string((int) Distance);

                                          tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                          DrawOutlinedText(HUD, FString(s), GrenadePos, COLOR_WHITE, COLOR_BLACK, true);
                                          tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                                       }
                                    }
                                 }
                        }
						
						std::vector<ASTExtraGameStateBase *> GameStateBase;
GetAllActors(GameStateBase);
for (auto actor = GameStateBase.begin(); actor != GameStateBase.end(); actor++)
{
auto InGame = *actor;
												
											if (Config.Asp.Gameİnfo) {
												std::string s;
                                s += "\nReal Players: ";
                                s += std::to_string((int) InGame->PlayerNum);
                                s += "\nTotal Alive Players: " ;
                                s += std::to_string((int) InGame->AlivePlayerNum);
                                s += "\nMatch Time  : ";
                                s += std::to_string((int) InGame->ElapsedTime);
                                s += "s | ";
                                s += std::to_string((int) InGame->ElapsedTime / 60);
                                s += "m";
                                tslFont->LegacyFontSize = 14;
                                DrawOutlinedText(HUD, FString(s), {(float) glWidth / 2.1 - 589.0f, 546.0f}, COLOR_WHITE, COLOR_BLACK, true);
                                tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                                }}
												
						
											                                if (Config.Asp.Genn) {
                                if (Actors[i]->IsA(ASTExtraGrenadeBase::StaticClass())) {
                                auto Genn = (ASTExtraGrenadeBase *) Actors[i];         
                                auto resa = getObjectPath(Genn);
                                if (strstr(resa, "BP_Grenade_Burn_C")){
                                if (!Genn->RootComponent)
                                continue;
                                float Distance = Genn->GetDistanceTo(localPlayer) / 100.f;      
                                //draw->AddText(NULL, 70.0f, ImVec2(glWidth / 3.0 - 50.f, 350), IM_COL32(255, 0, 0, 255), " MOVE, MOVE, MOVE ");}}
                                FVector2D GrenadePos2;                 
                                if (W2S(Genn->K2_GetActorLocation(), &GrenadePos2)) {             
                                std::string s;
                                s += "           MOLOTOV ";
                                s += std::to_string((int) Distance);
                                s += " m";
                                if (Distance <= 50.f) {
                                        
                                tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                          DrawOutlinedText(HUD, FString(s), GrenadePos2, COLOR_WHITE, COLOR_BLACK, true);
                                          tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                                          
                                      //   DrawImage(GrenadePos2.X, GrenadePos2.Y, 37, 37, mmolotov.textureId);
                                    //      DrawImage((int) (GrenadePos.X - 20), (int) (GrenadePos.Y - 45), 40, 40, mmolotov.textureId);       
                                          }}}}}
										  
										  
										  
										  if (Config.Asp.Air) {
                    if (Actors[i]->IsA(AAirDropBoxActor::StaticClass())) {
                        auto DropBox = (AAirDropBoxActor *) Actors[i];

                        auto Mesh = DropBox->RootComponent;
                        if (!Mesh)
                            continue;
                        float Distance = DropBox->GetDistanceTo(localPlayer) / 100.f;
                        FVector2D DropBoxPos;
                        if (W2S(DropBox->K2_GetActorLocation(), &DropBoxPos)) {
                        
                            std::string s = "AirDrop";
                            s += " [";
                            s += std::to_string((int) Distance);
                            s += "M]";
                      //      DrawImage(DropBoxPos.X, DropBoxPos.Y, 37, 37, Airee.textureId);                 
                            if (Distance <= 1000.f) {
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), DropBoxPos,COLOR_YELOW, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                                        
                                        

                        }
                    }
                }}
                       
										  if (Config.Asp.Plane) {
                    if (Actors[i]->IsA(AAirDropPlane::StaticClass())) {
                        auto AirDropPlane = (AAirDropPlane *) Actors[i];

                        auto Mesh = AirDropPlane->RootComponent;
                        if (!Mesh)
                            continue;
                        float Distance = AirDropPlane->GetDistanceTo(localPlayer) / 100.f;
                        FVector2D AirDropPlanePos;
                        if (W2S(AirDropPlane->K2_GetActorLocation(), &AirDropPlanePos)) {
                            std::string s = "Plane";
                            s += " [";
                            s += std::to_string((int) Distance);
                            s += "M]";
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), AirDropPlanePos,COLOR_LIME, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;

                        }
                    }
                }		
										  
										                         if (Config.Asp.LootBox) {
                           
                     if (Actors[i]->IsA(APickUpListWrapperActor::StaticClass())) {
                                auto Pick = (APickUpListWrapperActor *) Actors[i];  
                                if (!Pick->RootComponent)
                                continue;
                         float Distance = Pick->GetDistanceTo(localPlayer) / 100.f;
                          FVector2D PickUpListsPos;
                          if (Distance <= 300.f) {
                                Vector3 origin, extends;
                            
                                        
                                         if (W2S(Pick->K2_GetActorLocation(), &PickUpListsPos)) {
                                    
                                   
                                       //std::string s;
                                std::string s = "Dead";
                                s += " - ";
                                s += std::to_string((int) Distance);
                                s += "M";
                                if (Distance <= 300.f) {
                                tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), PickUpListsPos, COLOR_BLACK,COLOR_LIME, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                                //        DrawImage(PickUpListsPos.X, PickUpListsPos.Y, 37, 37, Deade.textureId);
								
                                 }}}}}
										  
                                          if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_BRDM_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "BRDM [";
                              s += std::to_string((int) Distance);
                              s += "m]";      
                              tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, BRDM.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                          if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_Scooter_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Scooter [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                              tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Scooter.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                          if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_Motorcycle")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Motorcycle [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Motorcycle.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                          if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_MotorcycleCart")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Motorcycle Cart [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, MotorcycleCart.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_Snowmobile_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Snow Mobile [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Snowmobile.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_Tuk")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Tuk Tuk [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Tuk.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Buggy")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Buggy [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Buggy.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Dacia")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Dacia [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Dacia.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "UAZ")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "UAZ [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, UAZ.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "PickUp_07_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Pick Up [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, PickUp.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Rony")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Rony [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Rony.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Mirado")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Mirado [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Mirado.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "MiniBus")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "MiniBus [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Minibus.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "PG117")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "PG117 [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, PG117.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "AquaRail")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "AquaRail [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, AquaRail.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Snowbike")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Snowbike [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Snowbike.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "CoupeRB")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "CoupeRB [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, CoupeRB.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Motorglider")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Motorglider [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Motorglider.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Monster")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Monster [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Monster.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "UTV")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "UTV [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, UTV.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "Bigfoot")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Bigfoot [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, Bigfoot.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "VH_ATV")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "ATV [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            tslFont->LegacyFontSize = std::max(5, 15 - (int) (Distance / 100));
                                        DrawOutlinedText(HUD, FString(s), CarPos, COLOR_WHITE, COLOR_BLACK, true);
                                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                              //DrawImage((int) (CarPos.X - 20), (int) (CarPos.Y - 45), 40, 40, ATV.textureId);                
                              
                                                                  
                              }                               }                               }                               }}
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "BP_LionDance_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Lion Dance [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            if (km_h >= 1.f) {   
                                                                    
                         } else {
                                
                              }                               }                               }                               }}
                              }

                          if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "BP_VehicleRadar_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Vehicle Radar [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            if (km_h >= 1.f) {   
                                                                    
                         } else {
                                
                              }                               }                               }                               }}
                              } 
                              
                              if (Config.Asp.Vehicle) {
                          if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];                                 
                              auto resa = getObjectPath(Vehicle);
                              if (strstr(resa, "UH60_Vehicle_C")){
                          if (!Vehicle->RootComponent)
                              continue;
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;                           
                            FVector2D CarPos;
                              if(Distance > 5.0f && Distance <= 500.0f){                                               
                           if (W2S(Vehicle->K2_GetActorLocation(), &CarPos)) {
               
                           std::string s;    
                           auto velocity = Vehicle->GetVelocity();
                           float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                           auto km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                              s += "Helicopter [";
                              s += std::to_string((int) Distance);
                              s += "m]";                                                                               
                            if (km_h >= 1.f) {   
                                                                    
                         } else {
                                
                              }                               }                               }                               }}
                              }
											
											
}}}}}}}}//END
g_LocalController = localController;
g_LocalPlayer = localPlayer;

// add count

if (Config.HandCam) {
        out = false;
    } else {
        out = true;
    }
     if (out) {

                       std::string fpd;            
fpd += "[Alert]";
fpd += " ";
fpd +=std::to_string((int)totalEnemies + totalBots);
fpd += " ";
fpd += "Enemies in Area";
tslFont->LegacyFontSize = 15;
DrawOutlinedText(HUD, FString(fpd), FVector2D(ScreenWidth / 2, 110), COLOR_RED, COLOR_BLACK, true);
}
}}}}}
void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1, int unk2) = 0;
void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1) {
if (Config.SilentAim.Enable) {
ASTExtraPlayerCharacter *Target = GetTargetByCrossDist();
if (Target) {
bool triggerOk = false;
        if (Config.SilentAim.Trigger != EAimTrigger::None) {
        if (Config.SilentAim.Trigger == EAimTrigger::Shooting) {
            triggerOk = g_LocalPlayer->bIsWeaponFiring;
        } else if (Config.SilentAim.Trigger == EAimTrigger::Scoping) {
             triggerOk = g_LocalPlayer->bIsGunADS;
        } else if (Config.SilentAim.Trigger == EAimTrigger::Both) {
             triggerOk = g_LocalPlayer->bIsWeaponFiring && g_LocalPlayer->bIsGunADS;
        } else if (Config.SilentAim.Trigger == EAimTrigger::Any) {
             triggerOk = g_LocalPlayer->bIsWeaponFiring || g_LocalPlayer->bIsGunADS;
        }} else triggerOk = true;
        if (triggerOk) {
             FVector targetAimPos = Target->GetBonePos("Head", {});
             targetAimPos.Z += 15.f;
        if (Config.SilentAim.Target == EAimTarget::Chest) {
              targetAimPos.Z -= 25.0f;}
        UShootWeaponEntity *ShootWeaponEntityComponent = thiz->ShootWeaponEntityComponent;
        if (ShootWeaponEntityComponent) {
        if (Config.SilentAim.Pred) {
        ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
        if (CurrentVehicle) {
        FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
        float dist = g_LocalPlayer->GetDistanceTo(Target);
        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
        targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel)); 
        targetAimPos.Z += LinearVelocity.Z * timeToTravel + 0.5 * Config.Line * timeToTravel * timeToTravel;
        } else {
        FVector Velocity = Target->GetVelocity();                                                                                                 
        float dist = g_LocalPlayer->GetDistanceTo(Target);                                                             
        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
        targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
        targetAimPos.Z += Velocity.Z * timeToTravel + 0.5 * Config.Line * timeToTravel * timeToTravel;
        }}
        FVector fDir = UKismetMathLibrary::Subtract_VectorVector(targetAimPos, g_LocalController->PlayerCameraManager->CameraCache.POV.Location);
        rot = UKismetMathLibrary::Conv_VectorToRotator(fDir);
        }}}}return orig_shoot_event(thiz, start, rot, weapon, unk1);}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Line(ImDrawList *draw,FVector2D origin, FVector2D dest, ImColor color)
{draw->AddLine({origin.X, origin.Y},{dest.X, dest.Y},color, 1.0f);}
void Box3D(ImDrawList *draw, Vector3 origin, Vector3 extends, ImColor col) {
origin -= extends / 2;
Vector3 one = origin;
Vector3 two = origin; two.X += extends.X;
Vector3 tree = origin; tree.X += extends.X; tree.Y += extends.Y;
Vector3 four = origin; four.Y += extends.Y;
Vector3 five = one; five.Z += extends.Z;
Vector3 six = two; six.Z += extends.Z;
Vector3 seven = tree; seven.Z += extends.Z;
Vector3 eight = four; eight.Z += extends.Z;
FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    Line(draw,s1, s2, col);
    Line(draw,s2, s3, col);
    Line(draw,s3, s4, col);
    Line(draw,s4, s1, col);
    Line(draw,s5, s6, col);
    Line(draw,s6, s7, col);
    Line(draw,s7, s8, col);
    Line(draw,s8, s5, col);
    Line(draw,s1, s5, col);
    Line(draw,s2, s6, col);
    Line(draw,s3, s7, col);
    Line(draw,s4, s8, col);}  

void DrawBoxEnemy(ImDrawList *draw, ImVec2 X, ImVec2 Y, float thicc, float rounding, int color) {
draw->AddLine({X.x, X.y}, {Y.x, Y.y}, color, thicc);}

void Box4Line(ImDrawList *draw, float thicc, int x, int y, int w, int h, int color) {
int iw = w / 4;
int ih = h / 4;
draw->AddRect(ImVec2(x, y),ImVec2(x + iw, y), color, thicc);
draw->AddRect(ImVec2(x + w - iw, y),ImVec2(x + w, y), color, thicc);
draw->AddRect(ImVec2(x, y),ImVec2(x, y + ih), color, thicc);
draw->AddRect(ImVec2(x + w - 1, y),ImVec2(x + w - 1, y + ih), color, thicc);;
draw->AddRect(ImVec2(x, y + h),ImVec2(x + iw, y + h), color, thicc);
draw->AddRect(ImVec2(x + w - iw, y + h),ImVec2(x + w, y + h), color, thicc);
draw->AddRect(ImVec2(x, y + h - ih), ImVec2(x, y + h), color, thicc);
draw->AddRect(ImVec2(x + w - 1, y + h - ih), ImVec2(x + w - 1, y + h), color, thicc);
}


void Box3D(ImDrawList *draw, FVector origin, FVector extends, ImColor col) {
        origin.X -= extends.X / 2.f;
        origin.Y -= extends.Y / 2.f;
        origin.Z -= extends.Z / 2.f;
        FVector one = origin;
        FVector two = origin; two.X += extends.X;
        FVector tree = origin; tree.X += extends.X; tree.Y += extends.Y;
        FVector four = origin; four.Y += extends.Y;
        FVector five = one; five.Z += extends.Z;
        FVector six = two; six.Z += extends.Z;
        FVector seven = tree; seven.Z += extends.Z;
        FVector eight = four; eight.Z += extends.Z;
        FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
        if (W2S2(one, &s1) && W2S2(two, &s2) && W2S2(tree, &s3) && W2S2(four, &s4) &&
        W2S2(five, &s5) && W2S2(six, &s6) && W2S2(seven, &s7) && W2S2(eight, &s8)){
        Line(draw,s1, s2, col);
        Line(draw,s2, s3, col);
        Line(draw,s3, s4, col);
        Line(draw,s4, s1, col);
        Line(draw,s5, s6, col);
        Line(draw,s6, s7, col);
        Line(draw,s7, s8, col);
        Line(draw,s8, s5, col);
        Line(draw,s1, s5, col);
        Line(draw,s2, s6, col);
        Line(draw,s3, s7, col);
        Line(draw,s4, s8, col);
        }}

    void Box3DV(ImDrawList *draw, Vector3 origin, Vector3 extends, ImColor col) {
    origin -= extends / 2;
 Vector3 one = origin;
 Vector3 two = origin; two.X += extends.X;
 Vector3 tree = origin; tree.X += extends.X; tree.Y += extends.Y;
 Vector3 four = origin; four.Y += extends.Y;
 Vector3 five = one; five.Z += extends.Z;
 Vector3 six = two; six.Z += extends.Z;
 Vector3 seven = tree; seven.Z += extends.Z;
 Vector3 eight = four; eight.Z += extends.Z;
    FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    Line(draw,s1, s2, col);
    Line(draw,s2, s3, col);
    Line(draw,s3, s4, col);
    Line(draw,s4, s1, col);
    Line(draw,s5, s6, col);
    Line(draw,s6, s7, col);
    Line(draw,s7, s8, col);
    Line(draw,s8, s5, col);
    Line(draw,s1, s5, col);
    Line(draw,s2, s6, col);
    Line(draw,s3, s7, col);
    Line(draw,s4, s8, col);
}  



int OpenURL(const char* url){
    JavaVM* java_vm = g_App->activity->vm;
    JNIEnv* java_env = NULL;
    jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
    if (jni_return == JNI_ERR)
        return -1;
    jni_return = java_vm->AttachCurrentThread(&java_env, NULL);
    if (jni_return != JNI_OK)
        return -2;
    jclass native_activity_clazz = java_env->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == NULL)
        return -3;
    jmethodID method_id = java_env->GetMethodID(native_activity_clazz, "AndroidThunkJava_LaunchURL", "(Ljava/lang/String;)V");
    if (method_id == NULL)
        return -4;
    jstring retStr = java_env->NewStringUTF(url);
    java_env->CallVoidMethod(g_App->activity->clazz, method_id, retStr);
    jni_return = java_vm->DetachCurrentThread();
    if (jni_return != JNI_OK)
        return -5;
    return 0;}
    
    

    
  const char *GetPackageName() {
    FILE *f = fopen("/proc/self/cmdline", "rb");
    if (f) {
        char *buf = new char[64];
        fread(buf, sizeof(char), 64, f);
        fclose(f);
        return buf;
    }return 0;}
    std::string getClipboardText() {
    if (!g_App)
        return "";
    auto activity = g_App->activity;
    if (!activity)
        return "";
    auto vm = activity->vm;
    if (!vm)
        return "";
    auto object = activity->clazz;
    if (!object)
        return "";
    std::string result;
    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    {
        auto ContextClass = env->FindClass("android/content/Context");
        auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
        auto str = env->NewStringUTF("clipboard");
        auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
        env->DeleteLocalRef(str);
        auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
        auto getText = env->GetMethodID(ClipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");
        auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
        auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString", "()Ljava/lang/String;");
        auto text = env->CallObjectMethod(clipboardManager, getText);
        if (text) {
            str = (jstring) env->CallObjectMethod(text, toStringMethod);
            result = env->GetStringUTFChars(str, 0);
            env->DeleteLocalRef(str);
            env->DeleteLocalRef(text);
        }
        env->DeleteLocalRef(CharSequenceClass);
        env->DeleteLocalRef(ClipboardManagerClass);
        env->DeleteLocalRef(clipboardManager);
        env->DeleteLocalRef(ContextClass);
    }
    vm->DetachCurrentThread();
    return result;
}

const char *GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
    jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
    return env->GetStringUTFChars(str, 0);
}
const char *GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());
    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}
const char *GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());
    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}
const char *GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());
    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}
const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());
    auto len = strlen(uuid);
    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);
    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
    jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());
    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}
struct MemoryStruct {
    char *memory;
    size_t size;
};
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;
    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}
std::string Login(const char *user_key) {
    if (!g_App)
        return "Internal Error";
    auto activity = g_App->activity;
    if (!activity)
        return "Internal Error";
    auto vm = activity->vm;
    if (!vm)
        return "Internal Error";
    auto object = activity->clazz;
    if (!object)
        return "Internal Error";
    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    std::string hwid = user_key;
    hwid += GetAndroidID(env, object);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);
    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());
    vm->DetachCurrentThread();
    std::string errMsg;
    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
     if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, /*POST*/ StrEnc(",IL=", "\x7C\x06\x1F\x69", 4).c_str());
        std::string api_key = OBFUSCATE("https://free.vip-pro.site/connect");
        curl_easy_setopt(curl, CURLOPT_URL, (api_key.c_str()));
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, /*https*/ StrEnc("!mLBO", "\x49\x19\x38\x32\x3C", 5).c_str());
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, /*Content-Type: application/x-www-form-urlencoded*/ StrEnc("@;Ls\\(KP4Qrop`b#d3094/r1cf<c<=H)AiiBG6i|Ta66s2[", "\x03\x54\x22\x07\x39\x46\x3F\x7D\x60\x28\x02\x0A\x4A\x40\x03\x53\x14\x5F\x59\x5A\x55\x5B\x1B\x5E\x0D\x49\x44\x4E\x4B\x4A\x3F\x04\x27\x06\x1B\x2F\x6A\x43\x1B\x10\x31\x0F\x55\x59\x17\x57\x3F", 47).c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            char data[4096];
        sprintf(data, /*game=PUBG&user_key=%s&serial=%s*/ StrEnc("qu2yXK,YkJyGD@ut0.u~Nb'5(:.:chK", "\x16\x14\x5F\x1C\x65\x1B\x79\x1B\x2C\x6C\x0C\x34\x21\x32\x2A\x1F\x55\x57\x48\x5B\x3D\x44\x54\x50\x5A\x53\x4F\x56\x5E\x4D\x38", 31).c_str(), user_key, UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                if (result[/*status*/ StrEnc("(>_LBm", "\x5B\x4A\x3E\x38\x37\x1E", 6).c_str()] == true) {
                    std::string token = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*token*/ StrEnc("{>3Lr", "\x0F\x51\x58\x29\x1C", 5).c_str()].get<std::string>();
                    time_t rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*rng*/ StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();
                    
               //     expiredDate = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*exdate*/ StrEnc("=So_ D", "\x58\x2B\x0B\x3E\x54\x21", 6).c_str()].get<std::string>();
                     if (rng + 30 > time(0)) {
                        std::string auth = /*PUBG*/ StrEnc("Q*) ", "\x01\x7F\x6B\x67", 4).c_str();;
                        auth += "-";
                        auth += user_key;
                        auth += "-";
                        auth += UUID;
                        auth += "-";
                        auth += /*Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E*/ StrEnc("-2:uwZdV^%]?{{wHs2V,+(^NJU;kC*_{", "\x7B\x5F\x02\x39\x1C\x6D\x31\x3C\x6C\x6F\x30\x4C\x11\x38\x27\x1E\x23\x64\x3C\x5E\x67\x49\x69\x34\x2D\x33\x43\x58\x36\x50\x66\x3E", 32).c_str();
                        std::string outputAuth = Tools::CalcMD5(auth);
                        g_Token = token;
                        g_Auth = outputAuth;
                        bValid = g_Token == g_Auth;
                        EXP = result["data"]["EXP"].get<std::string>();
                    }
                } else {
                    errMsg = result[/*reason*/ StrEnc("LW(3(c", "\x3E\x32\x49\x40\x47\x0D", 6).c_str()].get<std::string>();
                }} catch (json::exception &e) {
                errMsg = "{";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += chunk.memory;
                errMsg += "}";
            } } else {
            errMsg = curl_easy_strerror(res);
        }}
    curl_easy_cleanup(curl);
    return bValid ? "OK" : errMsg;}
	

auto noww = std::chrono::high_resolution_clock::now();
auto elapsedd = std::chrono::duration_cast<std::chrono::milliseconds>(noww - start).count();

namespace Settings
{
    static int Tab = 0;
}

    EGLBoolean (*orig_GLThreadSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _GLThreadSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    if (glWidth <= 0 || glHeight <= 0)
        return orig_GLThreadSwapBuffers(dpy, surface);

    if (!g_App)
        return orig_GLThreadSwapBuffers(dpy, surface);


    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);
    if (!initImGui) {
    InitTexture();       
    ImGui::CreateContext();


ImGuiStyle& Style = ImGui::GetStyle();

    Style.GrabMinSize = 2.0f;
    Style.GrabRounding = 0.0f;
   Style.ScrollbarSize = 19.0f;
	Style.WindowRounding = 6.000f;    
    Style.WindowBorderSize = 2.5f;
    Style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	Style.WindowTitleAlign = ImVec2(0.5, 0.5);
		Style.Colors[ImGuiCol_Text]               = ImColor(255, 255, 255, 255);
	Style.Colors[ImGuiCol_TitleBg]               = ImColor(15, 15, 15, 180);
	Style.Colors[ImGuiCol_TitleBgActive]               = ImColor(15, 15, 15, 180);
	Style.Colors[ImGuiCol_TitleBgCollapsed]               = ImColor(15, 15, 15, 180);
    Style.Colors[ImGuiCol_SliderGrab] = ImColor(172, 99, 52, 200);
    Style.Colors[ImGuiCol_SliderGrabActive] = ImColor(172, 99, 52, 200);
    Style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 210);
	Style.Colors[ImGuiCol_Tab] = ImColor(15, 15, 15, 210);
    Style.Colors[ImGuiCol_Button] = ImColor(255, 255, 0, 200);
	Style.Colors[ImGuiCol_Border] = ImColor(77, 80, 87, 255);
        
      
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");





            RenderingFPS.SetFps(Config.FPSControlSize);
RenderingFPS.AotuFPS_init();
RenderingFPS.setAffinity();
        ImGuiIO &io = ImGui::GetIO();
        struct timespec current_timespec;
static double g_Time = 0.0;
clock_gettime(CLOCK_MONOTONIC, &current_timespec);
double current_time = (double)(current_timespec.tv_sec)+(current_timespec.tv_nsec / 1000000000.0);
ImGui::GetIO().DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / Config.FPSControlSize);
g_Time = current_time;

        io.ConfigWindowsMoveFromTitleBarOnly = false;
        io.IniFilename = NULL;

    
        
    	   io.Fonts->AddFontFromMemoryTTF((void *)Custom_data, Custom_size, 20.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	memset(&Config, 0, sizeof(sConfig));
	
    
    


        Config.ColorsESP.BotVisLine = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.BotHideLine = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.PlayerVisLine = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.PlayerHideLine = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BotVisBox = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.BotHideBox = CREATE_COLOR(255, 255, 0, 255);
        Config.ColorsESP.PlayerVisBox = CREATE_COLOR(0, 0, 0, 255);
        Config.ColorsESP.PlayerHideBox = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BotVisSkeleton = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.BotHideSkeleton = CREATE_COLOR(200, 200, 0, 255);
        Config.ColorsESP.PlayerVisSkeleton = CREATE_COLOR(0, 0, 255, 255);
        Config.ColorsESP.PlayerHideSkeleton = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BotRadar = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.PlayerRadar = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.BotAlert = CREATE_COLOR(255, 255, 0, 255);
        Config.ColorsESP.PlayerAlert = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.Fov = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.Fova = CREATE_COLOR(0, 0, 255, 255);
        FOVT = 4.5f;
        FOVTB = 4.7f;
        Config.SilentAim.Pred = true;
        Config.Prid = 600.0f;
        Config.SilentAim.TargetLine = true;
        Config.AimBot.TargetLine = true;
        Config.IpadS = 87.0f;
        Config.SilentAim.Cross  = 350.0f;
        Config.AimBot.Cross  = 400.0f;
        Config.SilentAim.Meter  = 400.0f;
        Config.AimBot.Meter  = 400.0f;
        Config.AimBot.Recc  = 1.01f;
        Config.RadarX = 2.3f;
        Config.RadarY = 100.0f;
        Config.Line = 1.4f;
        Config.Skeleton = 1.3f;
        Config.Loot = 99.0f;
        initImGui = true;
        initImGui = true;
        for (auto &i : items_data) {
        for (auto &item : i["Items"]) {
        int r, g, b;
        sscanf(item["itemTextColor"].get<std::string>().c_str(), "#%02X%02X%02X", &r, &g, &b);
        ItemColors[item["itemId"].get<int>()] = CREATE_COLOR(r, g, b, 255);
        }}initImGui = true;}

        ImGuiIO &io = ImGui::GetIO();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
        ImGui::NewFrame();
  //      DrawESP(ImGui::GetBackgroundDrawList());
static bool Showw = true;
for (int i = 0; i < ImGuiKey_LegacyNativeKey_END; i++) {
if (ImGui::IsKeyDown((ImGuiKey)i)) {
Showw = true;
}}
if (Showw) {
    
    ImGui::SetNextWindowSize(ImVec2(800,520));
ImGui::SetNextWindowPos(ImVec2((float) glWidth / 1.98 - 400, 45.0f), ImGuiCond_Once);
ImGui::Begin(("Reohecks Project - X" ), &Showw ,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove); {
     static bool isLogin = false;
static std::string err;

if (!isLogin) {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Login Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImVec2 windowCenter = ImVec2(ImGui::GetWindowWidth() / 2.0f, ImGui::GetWindowHeight() / 2.0f);
    ImGui::SetCursorPosY(windowCenter.y - 150);  // vertical centering

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 20));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.3f, 1.0f)); // green
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.5f, 0.2f, 1.0f));

    ImGui::SetCursorPosX(windowCenter.x - 200);
    ImGui::Text("Welcome to the Login Page");

    ImGui::Spacing();
    ImGui::SetCursorPosX(windowCenter.x - 200);
    static char license[64] = "";
    ImGui::PushItemWidth(400);
    ImGui::InputTextWithHint("##key", "Paste or enter your license key", license, sizeof(license));
    ImGui::PopItemWidth();

    ImGui::Spacing();
    ImGui::SetCursorPosX(windowCenter.x - 200);
    if (ImGui::Button("Paste License from Clipboard", ImVec2(190, 45))) {
        auto key = getClipboardText();
        strncpy(license, key.c_str(), sizeof license);
    }
    ImGui::SameLine();
    if (ImGui::Button("Login Now", ImVec2(190, 45))) {
        err = Login(license);
        if (err == "OK") {
            isLogin = bValid && g_Auth == g_Token;
        }
    }

    if (!err.empty() && err != "OK") {
        ImGui::Spacing();
        ImGui::SetCursorPosX(windowCenter.x - 200);
        ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "Error: %s", err.c_str());
    }

    ImGui::Spacing();
    ImGui::SetCursorPosX(windowCenter.x - 200);
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::SetCursorPosX(windowCenter.x - 200);
    ImGui::Text("Don't have a license?");
    ImGui::SetCursorPosX(windowCenter.x - 200);
    if (ImGui::Button("Join Telegram", ImVec2(400, 45))) {
        OpenURL("https://t.me/Reohecks");
    }

 } else{ 
if (!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) {        
		
ImGui::Columns(2);
ImGui::SetColumnOffset(1, 160);
{
LeGo = true;
ImGui::Image((ImTextureID)lee.textureId, ImVec2(155, 150));
if(ImGui::OptButton1("Main", ImVec2(140,40))) {Settings::Tab = 0;}

if(ImGui::OptButton1("Esp", ImVec2(140,40))) {Settings::Tab = 1;}
                
					
					if(ImGui::OptButton1("Mod", ImVec2(140,40))) {Settings::Tab = 2;}
                
					
               if(ImGui::OptButton1("Aim", ImVec2(140,40))) {Settings::Tab = 3;}
               
               if(ImGui::OptButton1("Skin", ImVec2(140,40))) {Settings::Tab = 4;}
               
ImGui::TextColored(ImColor(135, 206, 250),"Key Buy :");                 
               if(ImGui::OptButton1(" Telegram ", ImVec2(140,40) )){OpenURL("https://t.me/Reohecks");}
                   
               
               }
               
               
ImGui::NextColumn();
{			
					
         //       ImGui::SetCursorPos(ImVec2(300,10));
		  		   ImGui::BeginChild("Afh","##Visuals", ImVec2(609, 475), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar); 
      {
        if (Settings::Tab == 0){
ImGui::Text("Click on the right >X< to close the floating window");
ImGui::Text("Click on the top >Volume Button< to open the floating window");
ImGui::TextColored(ImColor(97, 167, 217, 255).Value, "Main Menu");
  ImGui::Separator();//分割线
  ImGui::TextColored(ImColor(97, 167, 217, 255).Value, "FPS Control");
  ImGui::RadioButton("60FPS", &Config.FPSControl, 0);
  ImGui::SameLine();//下一个
  ImGui::RadioButton("90FPS", &Config.FPSControl, 1);
  ImGui::SameLine();//下一个
  ImGui::RadioButton("120FPS", &Config.FPSControl, 2);
  ImGui::SameLine();//下一个
  ImGui::RadioButton("144FPS", &Config.FPSControl, 3);
  if (Config.FPSControl == 0) {
 Config.FPSControlSize = 60;
  }
  if (Config.FPSControl == 1) {
 Config.FPSControlSize = 90;
  }
  if (Config.FPSControl == 2) {
 Config.FPSControlSize = 120;
  }
  if (Config.FPSControl == 3) {
 Config.FPSControlSize = 144;
  }
  ImGui::Checkbox("Hide Streaming", &Config.HandCam);
  static bool ok;
if (ImGui::Checkbox("HandCam Mode", &ok)) {
Showw = false;
Config.AimBot.Enable = false;
} else {

}
ImGui::TextColored(ImColor(97, 167, 217, 255).Value, "Play Safe");
  ImGui::TextColored(ImColor(97, 167, 217, 255).Value, " Get Package Name");
  ImGui::Text(GetPackageName());
  ImGui::TextColored(ImColor(97, 167, 217, 255).Value, "Rest Data");
  for (int i = 0; i < 1; i++) {
 if (i > 0)
 //获取ID
 ImGui::PushID(i);
 //样式
 if (ImGui::Button("Reset(1)",ImVec2(120, 32))) {
std::string DeleData;
DeleData += "rm -rf /storage/emulated/0/Android/data/";
DeleData += GetPackageName();
DeleData += "/cache";
system(DeleData.c_str());
 }
 ImGui::SameLine();//下一个
 if (ImGui::Button("Reset(2)",ImVec2(120, 32))) {
std::string DeleData;
DeleData += "rm -rf /storage/emulated/0/Android/data/";
DeleData += GetPackageName();
DeleData += "/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Logs";
system(DeleData.c_str());
std::string DeleData2;
DeleData2 += "rm -rf /storage/emulated/0/Android/data/";
DeleData2 += GetPackageName();
DeleData2 += "/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/LightData";
system(DeleData2.c_str());
 }
 ImGui::PopID();
  }

if (ImGui::Button("Report Block", ImVec2(300, 45))){
system(OBFUSCATE("rm -rf /data/data/com.pubg.krmobile/shared_prefs"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.krmobile/databases"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.krmobile/cache"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.krmobile/app_crashKit"));
                system(OBFUSCATE("rm -rf /data/data/com.pubg.krmobile/app_webview"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/cache*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/cacheFile.txt"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/login-identifier.txt"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Avatar*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Collision_Detection"));
 
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Demos/UserReplay*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/ImageDownload*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/ImageDownloadMgr"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Logs*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/MMKV*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/RoleInfo*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/GameErrorNoRecords"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.pubg.krmobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/StatEventReportedFlag"));
                
                system(OBFUSCATE("rm -rf /data/data/com.tencent.ig/shared_prefs"));
                system(OBFUSCATE("rm -rf /data/data/com.tencent.ig/databases"));
                system(OBFUSCATE("rm -rf /data/data/com.tencent.ig/cache"));
                system(OBFUSCATE("rm -rf /data/data/com.tencent.ig/app_crashKit"));
                system(OBFUSCATE("rm -rf /data/data/com.tencent.ig/app_webview"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/cache*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/cacheFile.txt"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/login-identifier.txt"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Avatar*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Collision_Detection"));
 
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Demos/UserReplay*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/ImageDownload*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/ImageDownloadMgr"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/Logs*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/MMKV*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/RoleInfo*"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/GameErrorNoRecords"));
                system(OBFUSCATE("rm -rf /storage/emulated/0/Android/data/com.tencent.ig/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/StatEventReportedFlag"));
                }		                    	
                
        }
					  if (Settings::Tab == 1){
								
						  
		        	   ImGui::Checkbox("Line", &Config.Linee);
//
						 ImGui::Checkbox("Health", &Config.Asp.Health);
						 ImGui::Checkbox("Skeleton", &Config.Asp.Skeleton);

						 ImGui::Checkbox("Name", &Config.Asp.Name);
						 ImGui::Checkbox("Box", &Config.Asp.Box);

						 ImGui::Checkbox("Distance", &Config.Asp.Distance);
						 ImGui::Checkbox("TeamID", &Config.Asp.TeamID);

						 ImGui::Checkbox("Game Info", &Config.Asp.Gameİnfo);
						 
					//	 ImGui::Checkbox("Alert", &Config.Asp.Alert);
						 
						   ImGui::Checkbox("Grenade", &Config.Asp.Genn);
						   
						   ImGui::Checkbox("LootBox", &Config.Asp.LootBox);

						   
						 ImGui::Checkbox("Vehicle", &Config.Asp.Vehicle);
					
					 
}
		 	 if (Settings::Tab == 2){
					 ImGui::Checkbox("Wide View", &Config.HighRisk.Ipad);
                ImGui::SliderFloat("Ipad Range", &Config.IpadS, 50.0f, 200.0f,"%.2f");                 
                
                              ImGui::Checkbox("120 Fps", &TeamNrg1);

}
					 
					 if (Settings::Tab == 3){
				
						   		ImGui::Checkbox("Enable AimBot", &Config.AimBot.Enable);

                ImGui::SliderInt("FOV Size", &Config.AimBot.Cross, 0.0f, 999.0f);

                ImGui::Checkbox("Visible Target Only", &Config.AimBot.VisCheck);                

                ImGui::Checkbox("Ignore Knock", &Config.AimBot.IgnoreKnocked);

                ImGui::Checkbox("Ignore Bot", &Config.AimBot.IgnoreBots);          
						
				
						 ImGui::Checkbox("Recoil Comp.", &Config.AimBot.Recoil);               
                ImGui::SliderFloat("Recoil", &Config.AimBot.Recc, 0.0f, 3.0f,"%.3f" );

                ImGui::SliderFloat("Aimbot Smoothness", &AimSmooth, 1.0f, 10.0f,"%.3f" );
						 
						    }
					 
					 
					if (Settings::Tab == 4){
					preferences.Outfit = true;
						static int Skin666 = 1;
						ImGui::Reohecks_New("Skin Mod Enable | Open In Match", &ModSkinn);
		
		 if (ImGui::Button("Gun Skin Enable",ImVec2(200, 42))) {
GunS = true;

preferences.M416 = true;
preferences.AKM = true;
preferences.SCARL = true;
preferences.M762 = true;
preferences.GROZA = true;
preferences.AUG = true;
preferences.KAR98 = true;
preferences.M16 = true;
preferences.M24 = true;
preferences.AWM = true;
preferences.DP28 = true;
preferences.M249 = true;
preferences.UZI = true;
preferences.UMP = true;
preferences.VECTOR = true;
preferences.PAN = true;
		 }
		 ImGui::SameLine();
		 if (ImGui::Button("Vehicle Skin",ImVec2(200, 42))) {
VehS = true;
preferences.Dacia = true;
preferences.CoupeRB = true;
preferences.UAZ = true;
preferences.Moto = true;
preferences.BigFoot = true;
preferences.Mirado = true;
preferences.Buggy = true;
preferences.MiniBus = true;
preferences.Boat = true;   
		 }
		 ImGui::SameLine();
	 if (ImGui::Button("Other Skin",ImVec2(200, 42))) {
FileS = true;
preferences.Bagg = true;
preferences.Helmett = true;
preferences.Emote = true;
preferences.Parachute = true;
		 }	 		  						

if (preferences.Config.Skin.XSuits == 0) {
ImGui::Text(" • Default");
} else if (preferences.Config.Skin.XSuits == 1) {
ImGui::Text(" • Blood Raven X-Suit");
} else if (preferences.Config.Skin.XSuits == 2) {
ImGui::Text(" • Golden Pharaoh X-Suit");
} else if (preferences.Config.Skin.XSuits == 3) {
ImGui::Text(" • Avalanche X-Suit");
} else if (preferences.Config.Skin.XSuits == 4) {
ImGui::Text(" • Irresidence");
} else if (preferences.Config.Skin.XSuits == 5) {
ImGui::Text(" • Poseidon");
} else if (preferences.Config.Skin.XSuits == 6) {
ImGui::Text(" • Arcane Jester X-suit");
}else if (preferences.Config.Skin.XSuits == 7) {
ImGui::Text(" • Silvanus X-Suit");
}else if (preferences.Config.Skin.XSuits == 8) {
ImGui::Text(" • Marmoris X-Suit");
}else if (preferences.Config.Skin.XSuits == 9) {
ImGui::Text(" • Fiore X-Suit");
}else if (preferences.Config.Skin.XSuits == 10) {
ImGui::Text(" • Stygian Liege X-Suit");
}else if (preferences.Config.Skin.XSuits == 11) {
ImGui::Text(" • Pharaoh 7 Level X-Suit");
}else if (preferences.Config.Skin.XSuits == 12) {
ImGui::Text(" • Ignis X-Suit");
}else if (preferences.Config.Skin.XSuits == 13) {
ImGui::Text(" • The Fool Set");
}else if (preferences.Config.Skin.XSuits == 14) {
ImGui::Text(" • Yellow Mummy");
}else if (preferences.Config.Skin.XSuits == 15) {
ImGui::Text(" • White Mummy");
}else if (preferences.Config.Skin.XSuits == 16) {
ImGui::Text(" • Gojo Set");
}else if (preferences.Config.Skin.XSuits == 17) {
ImGui::Text(" • Psychophage Set");
}else if (preferences.Config.Skin.XSuits == 18) {
ImGui::Text(" • Flamewraith Set");
}else if (preferences.Config.Skin.XSuits == 19) {
ImGui::Text(" • Glacial Bride Set");
}else if (preferences.Config.Skin.XSuits == 20) {
ImGui::Text(" • Suits Yugi");
}else if (preferences.Config.Skin.XSuits == 21) {
ImGui::Text(" • Suits Yugi 1");
}else if (preferences.Config.Skin.XSuits == 22) {
ImGui::Text(" • Suits Yugi 2");
}else if (preferences.Config.Skin.XSuits == 23) {
ImGui::Text(" • Shinobi Spirit Set");
}else if (preferences.Config.Skin.XSuits == 24) {
ImGui::Text(" • New Set");
}else if (preferences.Config.Skin.XSuits == 25) {
ImGui::Text(" • Manor Mage Set");
}else if (preferences.Config.Skin.XSuits == 26) {
ImGui::Text(" • Bape Set");
}else if (preferences.Config.Skin.XSuits == 27) {
ImGui::Text(" • Winter Highness Set");
}else if (preferences.Config.Skin.XSuits == 28) {
ImGui::Text(" • Panthera Prime Set");
}else if (preferences.Config.Skin.XSuits == 29) {
ImGui::Text(" • Yippee Yeti Set");
}else if (preferences.Config.Skin.XSuits == 30) {
ImGui::Text(" • Foxy Flare Set");
}else if (preferences.Config.Skin.XSuits == 31) {
ImGui::Text(" • The Fool's Delight Set");
}else if (preferences.Config.Skin.XSuits == 32) {
ImGui::Text(" • Sleepy Bunny Set");
}else if (preferences.Config.Skin.XSuits == 33) {
ImGui::Text(" • Lunahowl Set");
}else if (preferences.Config.Skin.XSuits == 34) {
ImGui::Text(" • Killua Character Set");
}else if (preferences.Config.Skin.XSuits == 35) {
ImGui::Text(" • Kurapika Character Set");
}else if (preferences.Config.Skin.XSuits == 36) {
ImGui::Text(" • Extreme Cyberwear Set");
}else if (preferences.Config.Skin.XSuits == 37) {
ImGui::Text(" • Golden Blessing Set (Female)");
}else if (preferences.Config.Skin.XSuits == 38) {
ImGui::Text(" • Lilac Finesse Set");
}else if (preferences.Config.Skin.XSuits == 39) {
ImGui::Text(" • SPYxFAMILY Twilight Set");
}else if (preferences.Config.Skin.XSuits == 40) {
ImGui::Text(" • SPYxFAMILY Princess Set");
}else if (preferences.Config.Skin.XSuits == 41) {
ImGui::Text(" • SPYxFAMILY ANYA");
}else if (preferences.Config.Skin.XSuits == 42) {
ImGui::Text(" • Chullax Set");
}else if (preferences.Config.Skin.XSuits == 43) {
ImGui::Text(" • Magick Delight Set");
}else if (preferences.Config.Skin.XSuits == 44) {
ImGui::Text(" • Street Stroller Set");
}else if (preferences.Config.Skin.XSuits == 45) {
ImGui::Text(" • City Casual Set");
}else if (preferences.Config.Skin.XSuits == 46) {
ImGui::Text(" • Seraphic Princess Set");
}else if (preferences.Config.Skin.XSuits == 47) {
ImGui::Text(" • Seraphic Genie Set");
}else if (preferences.Config.Skin.XSuits == 48) {
ImGui::Text(" • Gilded Wings Set");
}else if (preferences.Config.Skin.XSuits == 49) {
ImGui::Text(" • Chic Boxhead Set");
}else if (preferences.Config.Skin.XSuits == 50) {
ImGui::Text(" • Patched Puppet Set");
}else if (preferences.Config.Skin.XSuits == 51) {
ImGui::Text(" • Suave Royal Set");
}else if (preferences.Config.Skin.XSuits == 52) {
ImGui::Text(" • FelineFighter Set");
}else if (preferences.Config.Skin.XSuits == 53) {
ImGui::Text(" • Magick Delight Set");
}else if (preferences.Config.Skin.XSuits == 54) {
ImGui::Text(" • Gallant Jockey Set");
}else if (preferences.Config.Skin.XSuits == 55) {
ImGui::Text(" • Limit Breaker Set");
}else if (preferences.Config.Skin.XSuits == 56) {
ImGui::Text(" • Vogue Vigor Set");
}else if (preferences.Config.Skin.XSuits == 57) {
ImGui::Text(" • Bunny Dessert Set");
}else if (preferences.Config.Skin.XSuits == 58) {
ImGui::Text(" • Punk Pink Set");
}else if (preferences.Config.Skin.XSuits == 59) {
ImGui::Text(" • Ethereal Flutter Set");
}else if (preferences.Config.Skin.XSuits == 60) {
ImGui::Text(" • Bunny Beauty Set");
}else if (preferences.Config.Skin.XSuits == 61) {
ImGui::Text(" • Yoga Bunny Set");
}else if (preferences.Config.Skin.XSuits == 62) {
ImGui::Text(" • Power of 9 Dragons Set");
}else if (preferences.Config.Skin.XSuits == 63) {
ImGui::Text(" • Horsem4n Set");
}else if (preferences.Config.Skin.XSuits == 64) {
ImGui::Text(" • Bunny Pilot Set");
}else if (preferences.Config.Skin.XSuits == 65) {
ImGui::Text(" • Celestial Sentinel Set");
}else if (preferences.Config.Skin.XSuits == 66) {
ImGui::Text(" • Phantom Streetwear Set");
}else if (preferences.Config.Skin.XSuits == 67) {
ImGui::Text(" • Silent Stalker Set");
}else if (preferences.Config.Skin.XSuits == 68) {
ImGui::Text(" • Elite Assassin Set");
}else if (preferences.Config.Skin.XSuits == 69) {
ImGui::Text(" • Runner (Green)");
}else if (preferences.Config.Skin.XSuits == 70) {
ImGui::Text(" • Runner (Coma)");
}else if (preferences.Config.Skin.XSuits == 71) {
ImGui::Text(" • Avant Garde Set");
}else if (preferences.Config.Skin.XSuits == 72) {
ImGui::Text(" • Orange on Black");
}else if (preferences.Config.Skin.XSuits == 73) {
ImGui::Text(" • Parachuter Set");
}else if (preferences.Config.Skin.XSuits == 74) {
ImGui::Text(" • Fairy Set");
}else if (preferences.Config.Skin.XSuits == 75) {
ImGui::Text(" • Succubus Set");
}else if (preferences.Config.Skin.XSuits == 76) {
ImGui::Text(" • Dark Succubus Set");
}else if (preferences.Config.Skin.XSuits == 77) {
ImGui::Text(" • Torabika Barista Set");
}else if (preferences.Config.Skin.XSuits == 78) {
ImGui::Text(" • Skeleton Set");
}else if (preferences.Config.Skin.XSuits == 79) {
ImGui::Text(" • Count Set");
}else if (preferences.Config.Skin.XSuits == 80) {
ImGui::Text(" • Enchanter Set");
}else if (preferences.Config.Skin.XSuits == 81) {
ImGui::Text(" • Vampire Set");
}else if (preferences.Config.Skin.XSuits == 82) {
ImGui::Text(" • Demon Hunter Set");
}else if (preferences.Config.Skin.XSuits == 83) {
ImGui::Text(" • Áo Dài");
}else if (preferences.Config.Skin.XSuits == 84) {
ImGui::Text(" • Classic Santa Suit");
}else if (preferences.Config.Skin.XSuits == 85) {
ImGui::Text(" • Reindeer Set");
}else if (preferences.Config.Skin.XSuits == 86) {
ImGui::Text(" • Rudolph Suit");
}else if (preferences.Config.Skin.XSuits == 87) {
ImGui::Text(" • Traveler's Set");
}else if (preferences.Config.Skin.XSuits == 88) {
ImGui::Text(" • Emperor Penguin Suit");
}else if (preferences.Config.Skin.XSuits == 89) {
ImGui::Text(" • Stylish Santa Suit");
}else if (preferences.Config.Skin.XSuits == 90) {
ImGui::Text(" • Nutcracker Suit");
}else if (preferences.Config.Skin.XSuits == 91) {
ImGui::Text(" • Werewolf Suit");
}else if (preferences.Config.Skin.XSuits == 92) {
ImGui::Text(" • Phantom Hunter Suit");
}else if (preferences.Config.Skin.XSuits == 93) {
ImGui::Text(" • Plague Prevention Suit");
}else if (preferences.Config.Skin.XSuits == 94) {
ImGui::Text(" • Godzilla Set");
}else if (preferences.Config.Skin.XSuits == 95) {
ImGui::Text(" • Invader Set");
}else if (preferences.Config.Skin.XSuits == 96) {
ImGui::Text(" • Moondrop Eterna Set");
}else if (preferences.Config.Skin.XSuits == 97) {
ImGui::Text(" • Bloodstained Nemesis Set");
}else if (preferences.Config.Skin.XSuits == 98) {
ImGui::Text(" • Noctum Sunder Set");
}else if (preferences.Config.Skin.XSuits == 99) {
ImGui::Text(" • Wrathful Neptune Set");
}else if (preferences.Config.Skin.XSuits == 100) {
ImGui::Text(" • Bloody Noon Set");
}else if (preferences.Config.Skin.XSuits == 101) {
ImGui::Text(" • Starsea Admiral Set");
}else if (preferences.Config.Skin.XSuits == 102) {
ImGui::Text(" • Tribal Hipster Set");
}else if (preferences.Config.Skin.XSuits == 103) {
ImGui::Text(" • Bio Agent Set");
}else if (preferences.Config.Skin.XSuits == 104) {
ImGui::Text(" • Deadly Dazzle Set");
}else if (preferences.Config.Skin.XSuits == 105) {
ImGui::Text(" • Sanguine Nightmare Set");
}else if (preferences.Config.Skin.XSuits == 106) {
ImGui::Text(" • Professional Butler Set");
}else if (preferences.Config.Skin.XSuits == 107) {
ImGui::Text(" • Home Consultant Set");
}else if (preferences.Config.Skin.XSuits == 108) {
ImGui::Text(" • Professional Butler Set");
}else if (preferences.Config.Skin.XSuits == 109) {
ImGui::Text(" • Close Companion Set");
}else if (preferences.Config.Skin.XSuits == 110) {
ImGui::Text(" • Close Companion Set");
}else if (preferences.Config.Skin.XSuits == 111) {
ImGui::Text(" • luminous Set");
}else if (preferences.Config.Skin.XSuits == 112) {
ImGui::Text(" • Sliver Guru");
}
					if (ImGui::SliderInt("Outfit", &preferences.Config.Skin.XSuits, 0, 112)){
if (prevXSuits != preferences.Config.Skin.XSuits) {
					start = std::chrono::high_resolution_clock::now();
					callFunction = true;
					prevXSuits = preferences.Config.Skin.XSuits;
					}
				}
if (ImGui::Button("Luminous Full",ImVec2(120, 80))) {
Luminous = 1;
preferences.Config.Skin.XSuits = 0;
		 }
ImGui::SameLine();	 		  
if (ImGui::Button("Bape Full",ImVec2(120, 80))) {
Luminous = 2;
preferences.Config.Skin.XSuits = 0;
		 }	 		  		 
if (ImGui::Button("Invader Full",ImVec2(120, 80))) {
Luminous = 3;
preferences.Config.Skin.XSuits = 0;
		 }	 		  	 
ImGui::SameLine();
if (ImGui::Button("Pharaoh's Full",ImVec2(120, 80))) {
Luminous = 4;
preferences.Config.Skin.XSuits = 0;
		 }	 		  
	  
	  
             
             
                
}

                }
      ImGui::EndChild();
				
                }
                
                 
 ImGui::SetCursorPos(ImVec2(300,480));
 ImGui::TextColored(ImColor(135, 206, 250),"• Key Expired :");  
ImGui::SameLine();
ImGui::TextColored(ImColor(0, 255, 0), EXP.c_str());		
 


    
						 
						 
				
				
				
				}
				}
				if (preferences.isStateChanged) {
        preferences.save();
    }
				}}
				
//ImGui::SetNextWindowSize(ImVec2(500,500));
if (FileS) {
Showw = false;
    ImGui::SetNextWindowSize(ImVec2(600,500));
//ImGui::SetNextWindowPos(ImVec2((float) glWidth / 1.98 - 400, 45.0f), ImGuiCond_Once);
ImGui::Begin(("Other Skin" ), &FileS ,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); {
//ImGui::Begin(("Weapons Skin" ), &FileS , ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize); {

if (ImGui::SliderFloat("Bag", &Bag_Skin, 0, 9)){
	if (Bag_Skin > 1) {
      preferences.bag = 1;}
	  if (Bag_Skin > 2){
      preferences.bag = 2;}
 if (Bag_Skin > 3){
      preferences.bag = 3;}
if (Bag_Skin > 4){
      preferences.bag = 4;}
 if (Bag_Skin > 5){
      preferences.bag = 5;}   
	  if (Bag_Skin > 6){
      preferences.bag = 6;}   
	  if (Bag_Skin > 7){
      preferences.bag = 7;}   
	  if (Bag_Skin > 8){
      preferences.bag = 8;} 
if (Bag_Skin > 9){
      preferences.bag = 9;}   
	}
			

if (ImGui::SliderFloat("Helmet", &Helmet_Skin, 0, 8)){
              
               if (Helmet_Skin > 1) {
      preferences.helmet = 1;}
	  if (Helmet_Skin > 2){
      preferences.helmet = 2;}
 if (Helmet_Skin > 3){
      preferences.helmet = 3;}
if (Helmet_Skin > 4){
      preferences.helmet = 4;}
 if (Helmet_Skin > 5){
      preferences.helmet = 5;}   
	  if (Helmet_Skin > 6){
      preferences.helmet = 6;}   
	  if (Helmet_Skin > 7){
      preferences.helmet = 7;}   
	  if (Helmet_Skin > 8){
      preferences.helmet = 8;} 
if (Helmet_Skin > 9){
      preferences.helmet = 9;}   
	  }
	  
if (ImGui::SliderFloat("Emote", &Emote_Skin, 0, 8)){
                
                if (Emote_Skin > 1) {
      ModEmote1 = 1;}
	  if (Emote_Skin > 2){
      ModEmote1 = 2;}
 if (Emote_Skin > 3){
      ModEmote1 = 3;}
if (Emote_Skin > 4){
      ModEmote1 = 4;}
 if (Emote_Skin > 5){
      ModEmote1 = 5;}   
	  if (Emote_Skin > 6){
      ModEmote1 = 6;}   
	  if (Emote_Skin > 7){
      ModEmote1 = 7;}   
	  if (Emote_Skin > 8){
      ModEmote1 = 8;} 


}
if (ImGui::SliderFloat("Parachute", &Parachute_Skin, 0, 16)){
	if (Parachute_Skin > 1) {
      preferences.Config.Skin.Parachute = 1;}
	  if (Parachute_Skin > 2){
      preferences.Config.Skin.Parachute = 2;}
 if (Parachute_Skin > 3){
      preferences.Config.Skin.Parachute = 3;}
if (Parachute_Skin > 4){
      preferences.Config.Skin.Parachute = 4;}
 if (Parachute_Skin > 5){
      preferences.Config.Skin.Parachute = 5;}   
	  if (Parachute_Skin > 6){
      preferences.Config.Skin.Parachute = 6;}   
	  if (Parachute_Skin > 7){
      preferences.Config.Skin.Parachute = 7;}   
	  if (Parachute_Skin > 8){
      preferences.Config.Skin.Parachute = 8;} 
if (Parachute_Skin > 9){
      preferences.Config.Skin.Parachute = 9;}   
	  if (Parachute_Skin > 10){
      preferences.Config.Skin.Parachute = 10;}  
	  if (Parachute_Skin > 11){
      preferences.Config.Skin.Parachute = 11;}  
	  if (Parachute_Skin > 12){
      preferences.Config.Skin.Parachute = 12;} 
	  if (Parachute_Skin > 13){
      preferences.Config.Skin.Parachute = 13;}  
	  if (Parachute_Skin > 14){
      preferences.Config.Skin.Parachute = 14;}  
	  if (Parachute_Skin > 15){
      preferences.Config.Skin.Parachute = 15;}  
	  if (Parachute_Skin > 16){
      preferences.Config.Skin.Parachute = 16;} 
	/*  ImGui::EndChild( );
				 }*/
	}
}}
if (GunS) {
Showw = false;
    ImGui::SetNextWindowSize(ImVec2(600,500));
ImGui::Begin(("Weapons Skin" ), &GunS ,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); {
if (ImGui::SliderFloat("M416", &M416_Skin, 0, 11)){
	if (M416_Skin > 0) {
      preferences.Config.Skin.M416 = 0;}
	if (M416_Skin > 1) {
      preferences.Config.Skin.M416 = 1;}
	  if (M416_Skin > 2){
      preferences.Config.Skin.M416 = 2;}
 if (M416_Skin > 3){
      preferences.Config.Skin.M416 = 3;}
if (M416_Skin > 4){
      preferences.Config.Skin.M416 = 4;}
 if (M416_Skin > 5){
      preferences.Config.Skin.M416 = 5;}   
	  if (M416_Skin > 6){
      preferences.Config.Skin.M416 = 6;}   
	  if (M416_Skin > 7){
      preferences.Config.Skin.M416 = 7;}   
	  if (M416_Skin > 8){
      preferences.Config.Skin.M416 = 8;} 
if (M416_Skin > 9){
      preferences.Config.Skin.M416 = 9;}   
	  if (M416_Skin > 10){
      preferences.Config.Skin.M416 = 10;}  
	  if (M416_Skin > 11){
      preferences.Config.Skin.M416 = 11;}  
	
	}

	

if (ImGui::SliderFloat("AKM", &AKM_Skin, 0, 11)){
	if (AKM_Skin > 0) {
      preferences.Config.Skin.AKM = 0;}
	if (AKM_Skin > 1) {
      preferences.Config.Skin.AKM = 1;}
	  if (AKM_Skin > 2){
      preferences.Config.Skin.AKM = 2;}
 if (AKM_Skin > 3){
      preferences.Config.Skin.AKM = 3;}
if (AKM_Skin > 4){
      preferences.Config.Skin.AKM = 4;}
 if (AKM_Skin > 5){
      preferences.Config.Skin.AKM = 5;}   
	  if (AKM_Skin > 6){
      preferences.Config.Skin.AKM = 6;}   
	  if (AKM_Skin > 7){
      preferences.Config.Skin.AKM = 7;}   
	  if (AKM_Skin > 8){
      preferences.Config.Skin.AKM = 8;} 
if (AKM_Skin > 9){
      preferences.Config.Skin.AKM = 9;}   
	  if (AKM_Skin > 10){
      preferences.Config.Skin.AKM = 10;}  
	  if (AKM_Skin > 11){
      preferences.Config.Skin.AKM = 11;}  
	
	}
	
	

if (ImGui::SliderFloat("SCARL", &SCARL_Skin, 0, 8)){
	if (SCARL_Skin > 0) {
      preferences.Config.Skin.Scar = 0;}
	if (SCARL_Skin > 1) {
      preferences.Config.Skin.Scar = 1;}
	  if (SCARL_Skin > 2){
      preferences.Config.Skin.Scar = 2;}
 if (SCARL_Skin > 3){
      preferences.Config.Skin.Scar = 3;}
if (SCARL_Skin > 4){
      preferences.Config.Skin.Scar = 4;}
 if (SCARL_Skin > 5){
      preferences.Config.Skin.Scar = 5;}   
	  if (SCARL_Skin > 6){
      preferences.Config.Skin.Scar = 6;}   
	  if (SCARL_Skin > 7){
      preferences.Config.Skin.Scar = 7;}   
	  if (SCARL_Skin > 8){
      preferences.Config.Skin.Scar = 8;} 
	
	}
	

if (ImGui::SliderFloat("M762", &M762_Skin, 0, 8)){
	
	if (M762_Skin > 0) {
      preferences.Config.Skin.M762 = 0;}
	if (M762_Skin > 1) {
      preferences.Config.Skin.M762 = 1;}
	  if (M762_Skin > 2){
      preferences.Config.Skin.M762 = 2;}
 if (M762_Skin > 3){
      preferences.Config.Skin.M762 = 3;}
if (M762_Skin > 4){
      preferences.Config.Skin.M762 = 4;}
 if (M762_Skin > 5){
      preferences.Config.Skin.M762 = 5;}   
	  if (M762_Skin > 6){
      preferences.Config.Skin.M762 = 6;}   
	  if (M762_Skin > 7){
      preferences.Config.Skin.M762 = 7;}   
	  if (M762_Skin > 8){
      preferences.Config.Skin.M762 = 8;} 
	}

if (ImGui::SliderFloat("Groza", &GROZA_Skin, 0, 7)){
	if (GROZA_Skin > 0) {
      preferences.Config.Skin.Groza = 0;}
	if (GROZA_Skin > 1) {
      preferences.Config.Skin.Groza = 1;}
	  if (GROZA_Skin > 2){
      preferences.Config.Skin.Groza = 2;}
 if (GROZA_Skin > 3){
      preferences.Config.Skin.Groza = 3;}
if (GROZA_Skin > 4){
      preferences.Config.Skin.Groza = 4;}
 if (GROZA_Skin > 5){
      preferences.Config.Skin.Groza = 5;}   
	  if (GROZA_Skin > 6){
      preferences.Config.Skin.Groza = 6;}   
	  if (GROZA_Skin > 7){
      preferences.Config.Skin.Groza = 7;}   
	  
	}

if (ImGui::SliderFloat("AUG", &AUG_Skin, 0, 3)){
	
	if (AUG_Skin > 0) {
      preferences.Config.Skin.AUG = 0;}
	if (AUG_Skin > 1) {
      preferences.Config.Skin.AUG = 1;}
	  if (AUG_Skin > 2){
      preferences.Config.Skin.AUG = 2;}
 if (AUG_Skin > 3){
      preferences.Config.Skin.AUG = 3;}
	}

if (ImGui::SliderFloat("M16A4", &AUG_Skin, 0, 5)){
	
	if (M16A4_Skin > 0) {
      preferences.Config.Skin.M16A4 = 0;}
	if (M16A4_Skin > 1) {
      preferences.Config.Skin.M16A4 = 1;}
	  if (M16A4_Skin > 2){
      preferences.Config.Skin.M16A4 = 2;}
 if (M16A4_Skin > 3){
      preferences.Config.Skin.M16A4 = 3;}
if (M16A4_Skin > 4){
      preferences.Config.Skin.M16A4 = 4;}
 if (M16A4_Skin > 5){
      preferences.Config.Skin.M16A4 = 5;}   
	}
	

if (ImGui::SliderFloat("KAR-98", &KAR98_Skin, 0, 6)){
	
	if (KAR98_Skin > 0) {
      preferences.Config.Skin.K98 = 0;}
	if (KAR98_Skin > 1) {
      preferences.Config.Skin.K98 = 1;}
	  if (KAR98_Skin > 2){
      preferences.Config.Skin.K98 = 2;}
 if (KAR98_Skin > 3){
      preferences.Config.Skin.K98 = 3;}
if (KAR98_Skin > 4){
      preferences.Config.Skin.K98 = 4;}
 if (KAR98_Skin > 5){
      preferences.Config.Skin.K98 = 5;}   
	  if (KAR98_Skin > 6){
      preferences.Config.Skin.K98 = 6;}   
	
	
	}

if (ImGui::SliderFloat("M24", &M24_Skin, 0, 6)){
	
	
	if (M24_Skin > 0) {
      preferences.Config.Skin.M24 = 0;}
	if (M24_Skin > 1) {
      preferences.Config.Skin.M24 = 1;}
	  if (M24_Skin > 2){
      preferences.Config.Skin.M24 = 2;}
 if (M24_Skin > 3){
      preferences.Config.Skin.M24 = 3;}
if (M24_Skin > 4){
      preferences.Config.Skin.M24 = 4;}
	

	}

if (ImGui::SliderFloat("AWM", &AWM_Skin, 0, 6)){
	
	if (AWM_Skin > 0) {
      preferences.Config.Skin.AWM = 0;}
	if (AWM_Skin > 1) {
      preferences.Config.Skin.AWM = 1;}
	  if (AWM_Skin > 2){
      preferences.Config.Skin.AWM = 2;}
 if (AWM_Skin > 3){
      preferences.Config.Skin.AWM = 3;}
if (AWM_Skin > 4){
      preferences.Config.Skin.AWM = 4;}
 if (AWM_Skin > 5){
      preferences.Config.Skin.AWM = 5;}   
	
}

if (ImGui::SliderFloat("DP-28", &DP28_Skin, 0, 4)){
	
	if (DP28_Skin > 0) {
      preferences.Config.Skin.DP28 = 0;}
	if (DP28_Skin > 1) {
      preferences.Config.Skin.DP28 = 1;}
	  if (DP28_Skin > 2){
      preferences.Config.Skin.DP28 = 2;}
 if (DP28_Skin > 3){
      preferences.Config.Skin.DP28 = 3;}
if (DP28_Skin > 4){
      preferences.Config.Skin.DP28 = 4;}
 
	
	}

if (ImGui::SliderFloat("M249", &M249_Skin, 0, 4)){
	
	if (M249_Skin > 0) {
      preferences.Config.Skin.M249 = 0;}
	if (M249_Skin > 1) {
      preferences.Config.Skin.M249 = 1;}
	  if (M249_Skin > 2){
      preferences.Config.Skin.M249 = 2;}
 if (M249_Skin > 3){
      preferences.Config.Skin.M249 = 3;}
if (M249_Skin > 4){
      preferences.Config.Skin.M249 = 4;}
	
	}

if (ImGui::SliderFloat("UZI", &UZİ_Skin, 0, 6)){
	
	if (UZİ_Skin > 0) {
      preferences.Config.Skin.UZI = 0;}
	if (UZİ_Skin > 1) {
      preferences.Config.Skin.UZI = 1;}
	  if (UZİ_Skin > 2){
      preferences.Config.Skin.UZI = 2;}
 if (UZİ_Skin > 3){
      preferences.Config.Skin.UZI = 3;}
if (UZİ_Skin > 4){
      preferences.Config.Skin.UZI = 4;}
 if (UZİ_Skin > 5){
      preferences.Config.Skin.UZI = 5;}   
	  if (UZİ_Skin > 6){
      preferences.Config.Skin.UZI = 6;}   
	  if (UZİ_Skin > 7){
      preferences.Config.Skin.UZI = 7;}   
	  if (UZİ_Skin > 8){
      preferences.Config.Skin.UZI = 8;} 
	}

if (ImGui::SliderFloat("UMP-45", &UMP_Skin, 0, 7)){
	
if (UMP_Skin > 0) {
      preferences.Config.Skin.UMP = 0;}
	if (UMP_Skin > 1) {
      preferences.Config.Skin.UMP = 1;}
	  if (UMP_Skin > 2){
      preferences.Config.Skin.UMP = 2;}
 if (UMP_Skin > 3){
      preferences.Config.Skin.UMP = 3;}
if (UMP_Skin > 4){
      preferences.Config.Skin.UMP = 4;}
 if (UMP_Skin > 5){
      preferences.Config.Skin.UMP = 5;}   
	  if (UMP_Skin > 6){
      preferences.Config.Skin.UMP = 6;}   
	  if (UMP_Skin > 7){
      preferences.Config.Skin.UMP = 7;}   
	
	
	}
	
	

if (ImGui::SliderFloat("Vector", &UMP_Skin, 0, 4)){
	
	if (VECTOR_Skin > 0) {
      preferences.Config.Skin.Vector = 0;}
	if (VECTOR_Skin > 1) {
      preferences.Config.Skin.Vector = 1;}
	  if (VECTOR_Skin > 2){
      preferences.Config.Skin.Vector = 2;}
 if (VECTOR_Skin > 3){
      preferences.Config.Skin.Vector = 3;}
if (VECTOR_Skin > 4){
      preferences.Config.Skin.Vector = 4;}
 if (VECTOR_Skin > 5){
      preferences.Config.Skin.Vector = 5;}   
	
	
	}
	

if (ImGui::SliderFloat("PAN", &PAN_Skin, 0, 9)){
	if (PAN_Skin > 0) {
      preferences.Config.Skin.Pan = 0;}
	if (PAN_Skin > 1) {
      preferences.Config.Skin.Pan = 1;}
	  if (PAN_Skin > 2){
      preferences.Config.Skin.Pan = 2;}
 if (PAN_Skin > 3){
      preferences.Config.Skin.Pan = 3;}
if (PAN_Skin > 4){
      preferences.Config.Skin.Pan = 4;}
 if (PAN_Skin > 5){
      preferences.Config.Skin.Pan = 5;}   
	  if (PAN_Skin > 6){
      preferences.Config.Skin.Pan = 6;}   
	  if (PAN_Skin > 7){
      preferences.Config.Skin.Pan = 7;}   
	  if (PAN_Skin > 8){
      preferences.Config.Skin.Pan = 8;} 
      if (PAN_Skin > 9){
      preferences.Config.Skin.Pan = 9;} 
	/*ImGui::EndChild( );
					}*/
	
	}
}}
if (VehS) {
Showw = false;
    ImGui::SetNextWindowSize(ImVec2(600,500));
ImGui::Begin(("Vehicle Skin" ), &VehS ,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); {
			ImGui::Spacing();
if (ImGui::SliderFloat("Dacia", &Dacia_Skin, 0, 21)){
	
	
if (Dacia_Skin > 0) {
      preferences.Config.Skin.Dacia = 0;}
if (Dacia_Skin > 1) {
      preferences.Config.Skin.Dacia = 1;}
	  if (Dacia_Skin > 2){
      preferences.Config.Skin.Dacia = 2;}
 if (Dacia_Skin > 3){
      preferences.Config.Skin.Dacia = 3;}
if (Dacia_Skin > 4){
      preferences.Config.Skin.Dacia = 4;}
 if (Dacia_Skin > 5){
      preferences.Config.Skin.Dacia = 5;}   
	  if (Dacia_Skin > 6){
      preferences.Config.Skin.Dacia = 6;}   
	  if (Dacia_Skin > 7){
      preferences.Config.Skin.Dacia = 7;}   
	  if (Dacia_Skin > 8){
      preferences.Config.Skin.Dacia = 8;} 
if (Dacia_Skin > 9){
      preferences.Config.Skin.Dacia = 9;}   
	  if (Dacia_Skin > 10){
      preferences.Config.Skin.Dacia = 10;}  
	  if (Dacia_Skin > 11){
      preferences.Config.Skin.Dacia = 11;}  
	  if (Dacia_Skin > 12){
      preferences.Config.Skin.Dacia = 12;} 
	  if (Dacia_Skin > 13){
      preferences.Config.Skin.Dacia = 13;}  
	  if (Dacia_Skin > 14){
      preferences.Config.Skin.Dacia = 14;}  
	  if (Dacia_Skin > 15){
      preferences.Config.Skin.Dacia = 15;}  
	  if (Dacia_Skin > 16){
      preferences.Config.Skin.Dacia = 16;}  
	  if (Dacia_Skin > 17){
      preferences.Config.Skin.Dacia = 17;}  
	  if (Dacia_Skin > 18){
      preferences.Config.Skin.Dacia = 18;}   
	  if (Dacia_Skin > 19){
      preferences.Config.Skin.Dacia = 19;}  
	  if (Dacia_Skin > 20){
      preferences.Config.Skin.Dacia = 20;} 
	  if (Dacia_Skin > 21){
      preferences.Config.Skin.Dacia = 21;} 
	  
	
	}

if (ImGui::SliderFloat("CoupeRP", &Coupe_Skin, 0, 42)){
		
		if (Coupe_Skin > 0) {
      preferences.Config.Skin.CoupeRP = 0;}
if (Coupe_Skin > 1) {
      preferences.Config.Skin.CoupeRP = 1;}
	  if (Coupe_Skin > 2){
      preferences.Config.Skin.CoupeRP = 2;}
 if (Coupe_Skin > 3){
      preferences.Config.Skin.CoupeRP = 3;}
if (Coupe_Skin > 4){
      preferences.Config.Skin.CoupeRP = 4;}
 if (Coupe_Skin > 5){
      preferences.Config.Skin.CoupeRP = 5;}   
	  if (Coupe_Skin > 6){
      preferences.Config.Skin.CoupeRP = 6;}   
	  if (Coupe_Skin > 7){
      preferences.Config.Skin.CoupeRP = 7;}   
	  if (Coupe_Skin > 8){
      preferences.Config.Skin.CoupeRP = 8;} 
if (Coupe_Skin > 9){
      preferences.Config.Skin.CoupeRP = 9;}   
	  if (Coupe_Skin > 10){
      preferences.Config.Skin.CoupeRP = 10;}  
	  if (Coupe_Skin > 11){
      preferences.Config.Skin.CoupeRP = 11;}  
	  if (Coupe_Skin > 12){
      preferences.Config.Skin.CoupeRP = 12;} 
	  if (Coupe_Skin > 13){
      preferences.Config.Skin.CoupeRP = 13;}  
	  if (Coupe_Skin > 14){
      preferences.Config.Skin.CoupeRP = 14;}  
	  if (Coupe_Skin > 15){
      preferences.Config.Skin.CoupeRP = 15;}  
	  if (Coupe_Skin > 16){
      preferences.Config.Skin.CoupeRP = 16;}  
	  if (Coupe_Skin > 17){
      preferences.Config.Skin.CoupeRP = 17;}  
	  if (Coupe_Skin > 18){
      preferences.Config.Skin.CoupeRP = 18;}   
	  if (Coupe_Skin > 19){
      preferences.Config.Skin.CoupeRP = 19;}  
	  if (Coupe_Skin > 20){
      preferences.Config.Skin.CoupeRP = 20;} 
	  if (Coupe_Skin > 21){
      preferences.Config.Skin.CoupeRP = 21;} 
      if (Coupe_Skin > 22){
      preferences.Config.Skin.CoupeRP = 22;} 
if (Coupe_Skin > 23){
      preferences.Config.Skin.CoupeRP = 23;} 
      if (Coupe_Skin > 24){
      preferences.Config.Skin.CoupeRP = 24;} 
      if (Coupe_Skin > 25){
      preferences.Config.Skin.CoupeRP = 25;} 
      if (Coupe_Skin > 26){
      preferences.Config.Skin.CoupeRP = 26;} 
      if (Coupe_Skin > 27){
      preferences.Config.Skin.CoupeRP = 27;} 
      if (Coupe_Skin > 28){
      preferences.Config.Skin.CoupeRP = 28;} 
      if (Coupe_Skin > 29){
      preferences.Config.Skin.CoupeRP = 29;} 
      if (Coupe_Skin > 30){
      preferences.Config.Skin.CoupeRP = 30;} 
      if (Coupe_Skin > 31){
      preferences.Config.Skin.CoupeRP = 31;} 
      if (Coupe_Skin > 32){
      preferences.Config.Skin.CoupeRP = 32;} 
      if (Coupe_Skin > 33){
      preferences.Config.Skin.CoupeRP = 33;} 
      if (Coupe_Skin > 32){
      preferences.Config.Skin.CoupeRP = 32;} 
        if (Coupe_Skin > 33){
      preferences.Config.Skin.CoupeRP = 33;}  
         if (Coupe_Skin > 34){
      preferences.Config.Skin.CoupeRP = 34;} 
      if (Coupe_Skin > 35){
      preferences.Config.Skin.CoupeRP = 35;} 
      if (Coupe_Skin > 36){
      preferences.Config.Skin.CoupeRP = 36;} 
      if (Coupe_Skin > 37){
      preferences.Config.Skin.CoupeRP = 37;} 
      if (Coupe_Skin > 38){
      preferences.Config.Skin.CoupeRP = 38;} 
      if (Coupe_Skin > 39){
      preferences.Config.Skin.CoupeRP = 39;} 
      if (Coupe_Skin > 40){
      preferences.Config.Skin.CoupeRP = 40;} 
      if (Coupe_Skin > 41){
      preferences.Config.Skin.CoupeRP = 41;} 
      if (Coupe_Skin > 42){
      preferences.Config.Skin.CoupeRP = 42;} 
	  
		}
if (ImGui::SliderFloat("UAZ", &UAZ_Skin, 0, 17)){
		
		if (UAZ_Skin > 0) {
      preferences.Config.Skin.UAZ = 0;}
if (UAZ_Skin > 1) {
      preferences.Config.Skin.UAZ = 1;}
	  if (UAZ_Skin > 2){
      preferences.Config.Skin.UAZ = 2;}
 if (UAZ_Skin > 3){
      preferences.Config.Skin.UAZ = 3;}
if (UAZ_Skin > 4){
      preferences.Config.Skin.UAZ = 4;}
 if (UAZ_Skin > 5){
      preferences.Config.Skin.UAZ = 5;}   
	  if (UAZ_Skin > 6){
      preferences.Config.Skin.UAZ = 6;}   
	  if (UAZ_Skin > 7){
      preferences.Config.Skin.UAZ = 7;}   
	  if (UAZ_Skin > 8){
      preferences.Config.Skin.UAZ = 8;} 
if (UAZ_Skin > 9){
      preferences.Config.Skin.UAZ = 9;}   
	  if (UAZ_Skin > 10){
      preferences.Config.Skin.UAZ = 10;}  
	  if (UAZ_Skin > 11){
      preferences.Config.Skin.UAZ = 11;}  
	  if (UAZ_Skin > 12){
      preferences.Config.Skin.UAZ = 12;} 
	  if (UAZ_Skin > 13){
      preferences.Config.Skin.UAZ = 13;}  
	  if (UAZ_Skin > 14){
      preferences.Config.Skin.UAZ = 14;}  
	  if (UAZ_Skin > 15){
      preferences.Config.Skin.UAZ = 15;}  
	  if (UAZ_Skin > 16){
      preferences.Config.Skin.UAZ = 16;}  
	  if (UAZ_Skin > 17){
      preferences.Config.Skin.UAZ = 17;}  
		
	}
	

if (ImGui::SliderFloat("MotoBike", &MotoBike_Skin, 0, 9)){
	
	if (MotoBike_Skin > 0) {
      preferences.Config.Skin.Moto = 0;}
if (MotoBike_Skin > 1) {
      preferences.Config.Skin.Moto = 1;}
	  if (MotoBike_Skin > 2){
      preferences.Config.Skin.Moto = 2;}
 if (MotoBike_Skin > 3){
      preferences.Config.Skin.Moto = 3;}
if (MotoBike_Skin > 4){
      preferences.Config.Skin.Moto = 4;}
 if (MotoBike_Skin > 5){
      preferences.Config.Skin.Moto = 5;}   
	  if (MotoBike_Skin > 6){
      preferences.Config.Skin.Moto = 6;}   
	  if (MotoBike_Skin > 7){
      preferences.Config.Skin.Moto = 7;}   
	  if (MotoBike_Skin > 8){
      preferences.Config.Skin.Moto = 8;} 
if (MotoBike_Skin > 9){
      preferences.Config.Skin.Moto = 9;}   
	}

if (ImGui::SliderFloat("BigFoot", &BigFoot_Skin, 0, 2)){
	if (BigFoot_Skin > 0) {
      preferences.Config.Skin.Bigfoot = 0;}
if (BigFoot_Skin > 1) {
      preferences.Config.Skin.Bigfoot = 1;}
	
	}

if (ImGui::SliderFloat("Mirado", &Mirado_Skin, 0, 2)){
	if (Mirado_Skin > 0) {
      preferences.Config.Skin.Mirado = 0;}
if (Mirado_Skin > 1) {
      preferences.Config.Skin.Mirado = 1;}
	
	
	}
	

if (ImGui::SliderFloat("Buggy", &Buggy_Skin, 0, 33)){
	if (Buggy_Skin > 0) {
      preferences.Config.Skin.Buggy = 0;}
if (Buggy_Skin > 1) {
      preferences.Config.Skin.Buggy = 1;}
	  if (Buggy_Skin > 2){
      preferences.Config.Skin.Buggy = 2;}
 if (Buggy_Skin > 3){
      preferences.Config.Skin.Buggy = 3;}
if (Buggy_Skin > 4){
      preferences.Config.Skin.Buggy = 4;}
 if (Buggy_Skin > 5){
      preferences.Config.Skin.Buggy = 5;}   
	  if (Buggy_Skin > 6){
      preferences.Config.Skin.Buggy = 6;}   
	  if (Buggy_Skin > 7){
      preferences.Config.Skin.Buggy = 7;}   
	  if (Buggy_Skin > 8){
      preferences.Config.Skin.Buggy = 8;} 
if (Buggy_Skin > 9){
      preferences.Config.Skin.Buggy = 9;}   
	  if (Buggy_Skin > 10){
      preferences.Config.Skin.Buggy = 10;}  
	  if (Buggy_Skin > 11){
      preferences.Config.Skin.Buggy = 11;}  
	  if (Buggy_Skin > 12){
      preferences.Config.Skin.Buggy = 12;} 
	  if (Buggy_Skin > 13){
      preferences.Config.Skin.Buggy = 13;}  
	  if (Buggy_Skin > 14){
      preferences.Config.Skin.Buggy = 14;}  
	  if (Buggy_Skin > 15){
      preferences.Config.Skin.Buggy = 15;}  
	  if (Buggy_Skin > 16){
      preferences.Config.Skin.Buggy = 16;}  
	  if (Buggy_Skin > 17){
      preferences.Config.Skin.Buggy = 17;}  
	  if (Buggy_Skin > 18){
      preferences.Config.Skin.Buggy = 18;}   
	  if (Buggy_Skin > 19){
      preferences.Config.Skin.Buggy = 19;}  
	  if (Buggy_Skin > 20){
      preferences.Config.Skin.Buggy = 20;} 
	  if (Buggy_Skin > 21){
      preferences.Config.Skin.Buggy = 21;} 
      if (Buggy_Skin > 22){
      preferences.Config.Skin.Buggy = 22;} 
if (Buggy_Skin > 23){
      preferences.Config.Skin.Buggy = 23;} 
      if (Buggy_Skin > 24){
      preferences.Config.Skin.Buggy = 24;} 
      if (Buggy_Skin > 25){
      preferences.Config.Skin.Buggy = 25;} 
      if (Buggy_Skin > 26){
      preferences.Config.Skin.Buggy = 26;} 
      if (Buggy_Skin > 27){
      preferences.Config.Skin.Buggy = 27;} 
      if (Buggy_Skin > 28){
      preferences.Config.Skin.Buggy = 28;} 
      if (Buggy_Skin > 29){
      preferences.Config.Skin.Buggy = 29;} 
      if (Buggy_Skin > 30){
      preferences.Config.Skin.Buggy = 30;} 
      if (Buggy_Skin > 31){
      preferences.Config.Skin.Buggy = 31;} 
      if (Buggy_Skin > 32){
      preferences.Config.Skin.Buggy = 32;} 
      if (Buggy_Skin > 33){
      preferences.Config.Skin.Buggy = 33;} 
	}
	

if (ImGui::SliderFloat("MiniBus", &MiniBus_Skin, 0, 12)){
	
	if (MiniBus_Skin > 0) {
      preferences.Config.Skin.MiniBus = 0;}
if (MiniBus_Skin > 1) {
      preferences.Config.Skin.MiniBus = 1;}
	  if (MiniBus_Skin > 2){
      preferences.Config.Skin.MiniBus = 2;}
 if (MiniBus_Skin > 3){
      preferences.Config.Skin.MiniBus = 3;}
if (MiniBus_Skin > 4){
      preferences.Config.Skin.MiniBus = 4;}
 if (MiniBus_Skin > 5){
      preferences.Config.Skin.MiniBus = 5;}   
	  if (MiniBus_Skin > 6){
      preferences.Config.Skin.MiniBus = 6;}   
	  if (MiniBus_Skin > 7){
      preferences.Config.Skin.MiniBus = 7;}   
	  if (MiniBus_Skin > 8){
      preferences.Config.Skin.MiniBus = 8;} 
if (MiniBus_Skin > 9){
      preferences.Config.Skin.MiniBus = 9;}   
	  if (MiniBus_Skin > 10){
      preferences.Config.Skin.MiniBus = 10;}  
	  if (MiniBus_Skin > 11){
      preferences.Config.Skin.MiniBus = 11;}  
	  if (MiniBus_Skin > 12){
      preferences.Config.Skin.MiniBus = 12;} 
	
	}

if (ImGui::SliderFloat("Boat", &PG117_Skin, 0, 11)){
	
	if (PG117_Skin > 0) {
      preferences.Config.Skin.Boat = 0;}
if (PG117_Skin > 1) {
      preferences.Config.Skin.Boat = 1;}
	  if (PG117_Skin > 2){
      preferences.Config.Skin.Boat = 2;}
 if (PG117_Skin > 3){
      preferences.Config.Skin.Boat = 3;}
if (PG117_Skin > 4){
      preferences.Config.Skin.Boat = 4;}
 if (PG117_Skin > 5){
      preferences.Config.Skin.Boat = 5;}   
	  if (PG117_Skin > 6){
      preferences.Config.Skin.Boat = 6;}   
	  if (PG117_Skin > 7){
      preferences.Config.Skin.Boat = 7;}   
	  if (PG117_Skin > 8){
      preferences.Config.Skin.Boat = 8;} 
if (PG117_Skin > 9){
      preferences.Config.Skin.Boat = 9;}   
	  if (PG117_Skin > 10){
      preferences.Config.Skin.Boat = 10;}  
	  if (PG117_Skin > 11){
      preferences.Config.Skin.Boat = 11;}  
	
					
					
					 
					
					
					
					}
					}}
				ImGui::End();
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				return orig_GLThreadSwapBuffers(dpy, surface);
}

int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);

int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent) {
    if (initImGui) {
        ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});
    }
    return orig_onInputEvent(app, inputEvent);
}

void * (*oProcessEvent)(UObject *pObj, UFunction *pFunc, void *pArgs);
void * hkProcessEvent(UObject *pObj, UFunction *pFunc, void *pArgs) {
	const char *EngineHUD = ("Function Engine.HUD.ReceiveDrawHUD");
    if (pFunc) {
        if (pFunc->GetFullName() == EngineHUD) {
            AHUD *pHUD = (AHUD *) pObj;
            if (pHUD) {
                auto Params = (AHUD_ReceiveDrawHUD_Params *) pArgs;
                if (Params) {
                   RenderESPPRIVATE(pHUD, Params->SizeX, Params->SizeY);
                }
            }
        }
    }
if( std::string(pObj->GetName().c_str()).find("DeadBoxAvatarComponent") != std::string::npos ) {
   UDeadBoxAvatarComponent *DeadBoxPointer = ( UDeadBoxAvatarComponent *) pObj; 
    if( std::string(pFunc->GetFullName().c_str()).find("GetLuaFilePath") != std::string::npos ) {
    uint32_t Key = DeadBoxPointer->IsSelf();              
    auto GWorld = GetWorld();
    if (GWorld){
        if (GWorld->NetDriver->ServerConnection)
            if(GWorld->NetDriver->ServerConnection->PlayerController){
    ASTExtraPlayerController *localController = (ASTExtraPlayerController *)GWorld->NetDriver->ServerConnection->PlayerController;
    ASTExtraPlayerCharacter *localPlayer = (ASTExtraPlayerCharacter *)localController->AcknowledgedPawn;
                if(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated){


if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M416")){        
if (preferences.M416){
            DeadBoxPointer->ChangeItemAvatar(new_Skin.M416_1, true);
            }
}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AKM")){
if (preferences.AKM) {
DeadBoxPointer->ChangeItemAvatar(new_Skin.AKM, true); // - AKM
}}

                            if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "SCAR-L")){
	                        if (preferences.SCARL) {
DeadBoxPointer->ChangeItemAvatar(new_Skin.Scar, true); // - Scar
}}
							
							if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M762")){                        
							
                            if (preferences.M762) {
                            DeadBoxPointer->ChangeItemAvatar(new_Skin.M762, true); //8-bit Unicorn - M762
                            }
							}
							
					    
				
						
						if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "GROZA")){                        
							
						if (preferences.GROZA) {
						DeadBoxPointer->ChangeItemAvatar(new_Skin.Groza, true);
}}
						
						
						if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "UZI")){                        
							
						if (preferences.UZI == 1) 
                        DeadBoxPointer->ChangeItemAvatar(new_Skin.UZI, true); //Savagery - UZI
                      
						}}
						
						
						if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "UMP")){                        
							
						if (preferences.UMP) {
                        DeadBoxPointer->ChangeItemAvatar(new_Skin.UMP, true);//Wrate Off Dragon Flame
}}
						
						if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "KAR")){                        
							
						if (preferences.KAR98) 
                        DeadBoxPointer->ChangeItemAvatar(new_Skin.K98, true); //Horror Teeth Mark
                        }                   
                        }
						
					    if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M24")){                        
							
						if (preferences.M24) {
                        DeadBoxPointer->ChangeItemAvatar(new_Skin.M24, true); //Raging Sea
                     
                           }}
                        
                            if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M16A4")){                        
							
						if (preferences.M16) {
                        DeadBoxPointer->ChangeItemAvatar(new_Skin.M16A4, true); //Raging Sea
}}
						
						
						if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AWM")){                        
							
						if (preferences.AWM) {
                        DeadBoxPointer->ChangeItemAvatar( new_Skin.AWM, true); //Purple Night
                        }}
						
	//MK14					
                        if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "Vector")){                                                                     
                    	if (preferences.VECTOR) {
                        DeadBoxPointer->ChangeItemAvatar( new_Skin.Vector, true); //Purple Night
}}
											
						
}}}

const char *pBroadCast = ("Function ShadowTrackerExtra.STExtraPlayerController.BroadcastFatalDamageToClientWithStruct");
    if (pFunc) {
        if (pFunc->GetFullName() == pBroadCast) {
            ASTExtraPlayerController *pController = (ASTExtraPlayerController *) pObj;
            if (pController) {
                auto Params = (ASTExtraPlayerController_BroadcastFatalDamageToClientWithStruct_Params *) pArgs;
                if (Params) {
    auto GWorld = GetWorld();
    if (GWorld){
        if (GWorld->NetDriver->ServerConnection)
            if(GWorld->NetDriver->ServerConnection->PlayerController){
    ASTExtraPlayerController *localController = (ASTExtraPlayerController *)GWorld->NetDriver->ServerConnection->PlayerController;
    ASTExtraPlayerCharacter *localPlayer = (ASTExtraPlayerCharacter *)localController->AcknowledgedPawn;
                if(localController->PlayerKey == Params->FatalDamageParameter.CauserKey && !localController->STExtraBaseCharacter->CurrentVehicle && localPlayer->WeaponManagerComponent->CurrentWeaponReplicated){
if (preferences.Outfit) {
Params->FatalDamageParameter.CauserClothAvatarID =  new_Skin.XSuits;//blood raven x suit
}
      if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AKM")){
Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.AKM;//Sculpture - AKM
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M416")){  
Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.M416_1;//Glacier - M416 
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "SCAR-L")){
Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.Scar;//Water Blaster - SCAR-L
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M762")){  
Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.M762;//Stray Rebellion - M762
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "GROZA")){
Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.Groza;
}

else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "UZI")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.UZI;//Shimmer Power - UZI
  
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "UMP45")){


Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.UMP;

  
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "Vector")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.Vector;
  
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "Kar98K")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.K98;  
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M24")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.M24;

}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AWM")){


Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.AWM;

}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "DP28")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.DP28;

}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M16A4")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.M16A4;
}
else if(strstr(localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M249")){

Params->FatalDamageParameter.CauserWeaponAvatarID = new_Skin.M249;

}
}}}}}}
return oProcessEvent(pObj, pFunc, pArgs);
}
}



void initOffset() {
    ProcessEvent_Offset = (UE4 + ProccesEvent_Offset);
    if (ProcessEvent_Offset) {
        Tools::Hook((void *) (ProcessEvent_Offset), (void *) hkProcessEvent,
                    (void **) &oProcessEvent);
    } else {
        LOGI("Failed");
    }
}
              
              
        #define SLEEP_TIME 1000LL / 60LL
     










void *Fuck_Hook(void *) {
	
	

	

return 0;}
__int64_t (*osub_12BA2C)(const char* a1, unsigned int a2);
__int64_t hsub_12BA2C(const char* a1, unsigned int a2) {
    std::this_thread::sleep_for(std::chrono::hours::max());
    return osub_12BA2C(a1, a2);
}



int ZeusClose() {
    JavaVM* java_vm = g_App->activity->vm;
    JNIEnv* java_env = NULL;
    jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
    if (jni_return == JNI_ERR)
        return -1;
    jni_return = java_vm->AttachCurrentThread(&java_env, NULL);
    if (jni_return != JNI_OK)
        return -2;
    jclass native_activity_clazz = java_env->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == NULL)
        return -3;
    jmethodID method_id = java_env->GetMethodID(native_activity_clazz, OBFUSCATE("AndroidThunkJava_RestartGame"),/*Zeus New Restart*/OBFUSCATE("()V"));
    if (method_id == NULL)
        return -4;
    java_env->CallVoidMethod(g_App->activity->clazz, method_id);
    jni_return = java_vm->DetachCurrentThread();
    if (jni_return != JNI_OK)
        return -5;
    return 0;
}
bool isZeusFolderHere(const std::string& folderPath) {
    return (access(folderPath.c_str(), F_OK) == 0);
}
void Zeus() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/com.guoshi.httpcanary");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus2() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/com.guoshi.httpcanary.premium");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus3() {
std::string folderPath = OBFUSCATE("/data/user/0/eu.faircode.netguard");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus4() {
std::string folderPath = OBFUSCATE("/data/user/0/com.guoshi.httpcanary.premium");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus5() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/com.sniffer");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus6() {
std::string folderPath = OBFUSCATE("/data/user/0/com.sniffer");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus7() {
std::string folderPath = OBFUSCATE("/data/user/0/com.guoshi.httpcanary");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus8() {
std::string folderPath = OBFUSCATE("/data/user/0/org.httpcanary.pro");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus9() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/com.datacapture.pro");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus10() {
std::string folderPath = OBFUSCATE("/data/user/0/com.datacapture.pro");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus11() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/com.httpcanary.pro");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus12() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/ROKMOD.COM");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
void Zeus13() {
std::string folderPath = OBFUSCATE("/storage/emulated/0/Android/data/com.sanmeet");
if (isZeusFolderHere(folderPath)) {
    ZeusClose(); } else {}
}
    void *main_thread(void *) {
Zeus(); Zeus2(); Zeus3(); Zeus4(); Zeus5(); Zeus6(); Zeus7(); Zeus8(); Zeus9(); Zeus10(); Zeus11(); Zeus12(); Zeus13(); 




//HOOK_LIB("libanort.so","0x12BA2C",hsub_12BA2C,osub_12BA2C);//crasfix
//PATCH_LIB("libanogs.so", "0x3DD9BC", "C0 03 5F D6");//GAME CRASH FIX

//MAKE BY @MODAMELLA
				
//by : @G_Pow2  Global 64BIT 3.2

        UE4 = Tools::GetBaseAddress("libUE4.so");
        while (!UE4) {
            UE4 = Tools::GetBaseAddress("libUE4.so");
            sleep(1);}
        while (!g_App) {
            g_App = *(android_app **) (UE4 + GNativeAndroidApp_Offset);
            sleep(1);}
			anogs = Tools::GetBaseAddress("libanogs.so");
        while (!anogs) {
            anogs = Tools::GetBaseAddress("libanogs.so");
            sleep(1);}
           
      
        while (!g_App->onInputEvent)
            sleep(1);
        orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
        g_App->onInputEvent = onInputEvent;
		
		
        FName::GNames = GetGNames();
        while (!FName::GNames) {
            FName::GNames = GetGNames();
            sleep(1); }
			
			
         UObject::GUObjectArray = (FUObjectArray *) (UE4 + GUObject_Offset);

//Tools::Hook((void*)(UE4 + 0xb2840e0), (void*)&eglSwapBuffers, (void**)&orig_eglSwapBuffers);
   Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib64/libandroid_runtime.so"), OBFUSCATE("eglSwapBuffers")), (void *) _GLThreadSwapBuffers, (void **) &orig_GLThreadSwapBuffers);
   preferences.load();
initOffset();
        pthread_t t;
        items_data = json::parse(JSON_ITEMS);	
		items_data = json::parse(JSON_ITEMS);
		items_data_r = json::parse(JSON_ITEMSA);
		items_data_sm = json::parse(JSON_ITEMSMG);
		items_data_sn = json::parse(JSON_ITEMSNI);
		items_data_h = json::parse(JSON_ITEMSH);
		items_data_ammo = json::parse(JSON_ITEMSAMMO);
		items_data_mag = json::parse(JSON_ITEMSMAG);
		items_data_scop = json::parse(JSON_ITEMSSCOPE);
		return 0;}

   __attribute__((constructor)) void _init() {
        pthread_t t;
		pthread_create(&t, 0, main_thread, 0);
		pthread_create(&t, 0, Fuck_Hook, 0);}
