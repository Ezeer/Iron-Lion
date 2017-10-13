#include "DXUT.h"
#include "SDKmisc.h"
#include "xnaCollision.h"

//PHYSICS
#define GROUND_Y 3.0f // -GROUND_Y is the Y coordinate of the ground.
#define GROUND_ABSORBANCE 0.2f // GROUND_ABSORBANCE is the percentage of the velocity absorbed by ground and walls when an ammo hits.
#define AMMO_ABSORBANCE 0.1f // AMMO_ABSORBANCE is the percentage of the velocity absorbed by ammos when two collide.
#define GRAVITY 3.0f  // GRAVITY defines the magnitude of the downward force applied to ammos.
#define DROID_VELOCITY 2.0f // MIN_VOL_ADJUST is the minimum volume adjustment based on contact velocity.
#define BOUNCE_TRANSFER 0.8f // BOUNCE_TRANSFER is the proportion of velocity transferred during a collision between 2 ammos.
#define BOUNCE_LOST 0.1f  // BOUNCE_LOST is the proportion of velocity lost during a collision between 2 ammos.
#define REST_THRESHOLD 0.005f // REST_THRESHOLD is the energy below which the ball is flagged as laying on ground.  // It is defined as Gravity * Height_above_ground + 0.5 * Velocity * Velocity
#define PHYSICS_FRAMELENGTH 0.003f // PHYSICS_FRAMELENGTH is the duration of a frame for physics handling when the graphics frame length is too long.
#define MAX_SOUND_VELOCITY 1.0f // MAX_SOUND_VELOCITY is the velocity at which the bouncing sound is played at maximum volume.  Higher velocity uses maximum volume.
#define MIN_SOUND_VELOCITY 0.07f  // MIN_SOUND_VELOCITY is the minimum contact velocity required to make a sound.
#define MIN_VOL_ADJUST 0.8f  // MIN_VOL_ADJUST is the minimum volume adjustment based on contact velocity.


#define MAX_AMMO 100  // MAX_AMMO is the maximum number of ammo that can exist in the world.
#define MAX_DROID 50
#define DROID_HITPOINTS 20
#define AMMO_SIZE 0.10f // AMMO_SIZE is the diameter of the ball mesh in the world.
#define DROID_SIZE 0.5f
#define DROID_MIN_HEIGHT 0.5f
#define DROID_HEIGHT_FLUX 0.5f
#define DROID_TURN_AI_PERCENT 40
#define DROID_MOVE_AI_PERCENT 40
#define DROID_MOVE_TIME_MIN  2000
#define DROID_MOVE_TIME_FLUX 3000
#define DROID_CREATE_DELAY_FLUX 2500
#define DROID_DEATH_SPEED 3.0f
#define AUTOFIRE_DELAY 0.1f  // AUTOFIRE_DELAY is the period between two successive ammo firing.
#define CAMERA_SIZE 0.2f // CAMERA_SIZE is used for clipping camera movement

// MinBound and MaxBound are the bounding box representing the cell mesh.
 const D3DXVECTOR3           g_MinBound( -6.0f, -GROUND_Y, -6.0f );
const D3DXVECTOR3           g_MaxBound( 6.0f, GROUND_Y, 6.0f );

extern enum AI_STATE
{
    AI_TURNING = 1,
    AI_MOVING,
    AI_STOPPED,
}aiState;

 struct DROID_STATE
{
    bool bActive;
    D3DXVECTOR3 vPosition;
    D3DXVECTOR3 vVelocity;

    D3DXVECTOR3 vNudgeVelocity;
    AI_STATE aiState;
    float fTargetRotation;
    D3DXQUATERNION qTarget;
    D3DXQUATERNION qStart;
    D3DXQUATERNION qCurrent;
    float fRotInterp;
    float fTaskTimer;
    int nHitPoints;
    float fDeathAnimation;
    float fAlpha;
    D3DXCOLOR Specular;
};
 struct DROID_STATE2 // future use with new datas ...
{
    bool bActive;
    D3DXVECTOR3 vPosition;
    D3DXVECTOR3 vVelocity;

    D3DXVECTOR3 vNudgeVelocity;
    AI_STATE aiState;
    float fTargetRotation;
    D3DXQUATERNION qTarget;
    D3DXQUATERNION qStart;
    D3DXQUATERNION qCurrent;
    float fRotInterp;
    float fTaskTimer;
    int nHitPoints;
    float fDeathAnimation;
    float fAlpha;
    D3DXCOLOR Specular;
	XNA::Sphere collisionSphere;
	CDXUTXFileMesh meshDroidCollision;// to debug collision...
};


struct AMMO_STATE
{
    D3DXMATRIXA16 mAmmoRot;
    bool bActive;    // True if ball is visible
    D3DXVECTOR3 vPosition;
    D3DXVECTOR3 vVelocity;

    D3DXVECTOR4 Diffuse;
    double fTimeCreated;
    float fLifeCountdown;
    float fAlpha;
    bool bGround;    // Whether it is laying on the ground (resting or rolling)
};
enum GAME_MODE
{   
	GAME_SPLASH  = 0,
    GAME_RUNNING = 1,
    GAME_MAIN_MENU,
    GAME_AUDIO_MENU,
    GAME_VIDEO_MENU,
    GAME_INPUT_MENU
};

 struct GAME_STATE
{
    AMMO_STATE      AmmoQ[MAX_AMMO];    // Queue of ammos in the world
    int nAmmoCount;         // Number of ammos that exist in the world
    float fAmmoColorLerp;
    D3DXCOLOR BlendToColor;
    D3DXCOLOR BlendFromColor;
    //DROID_STATE     DroidQ[MAX_DROID]; deprecated
    DROID_STATE2     DroidQ[MAX_DROID];//use of Collision mesh for debug and more
    int nDroidCount;
    int nMaxDroids;

    bool bDroidCreate;
    bool bMassDroidKill;
    float fDroidCreateCountdown;

    bool bDroidMove;
    bool bAutoAddDroids;

    DXUT_GAMEPAD    gamePad[DXUT_MAX_CONTROLLERS]; // XInput controller state

    GAME_MODE gameMode;
};
void DroidPickNewDirection( int A );