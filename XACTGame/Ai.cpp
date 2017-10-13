#include "Ai.h"
#include "DXUT.h"
#include "SDKmisc.h"
//#include "game.h"
//externs
extern GAME_STATE g_GameState;
enum AI_STATE aiState;

///*****************************************************
/// PART OF AI
///HOW TO CALL IT IN A LUA SCRIPT ?

//--------------------------------------------------------------------------------------

float GetDistFromWall( D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3, D3DXVECTOR3 N )
{
    // Plane equation: N dot (P-P3) = 0 where P3 and points P are on plane and N is plane normal 
    // Line equation: P = P1 + u(P2-P1) where points P on line pass through points P1 and P2
    // Intersection is when: N dot ((P1+u(P2-P1))-P3)=0 
    //                    or N dot (P1+u(P2-P1))=N dot P3
    //                    or u=[N dot (P3-P1)]/[N dot(P2-P1)]

    D3DXVECTOR3 P3minusP1;
    D3DXVECTOR3 P2minusP1;
    D3DXVec3Subtract( &P3minusP1, &P3, &P1 );
    D3DXVec3Subtract( &P2minusP1, &P2, &P1 );
    float a = D3DXVec3Dot( &N, &P3minusP1 );
    float b = D3DXVec3Dot( &N, &P2minusP1 );
    if( b < 0.01f )
    {
        float u = a / b;
        D3DXVECTOR3 PonLineInterestingPlane = P1 + u * P2minusP1;
        D3DXVECTOR3 P1ToP = P1 - PonLineInterestingPlane;
        float fDist = D3DXVec3Length( &P1ToP );

        return fDist;
    }
    else
    {
        return 9999999.0f;
    }
}


void DroidPickNewDirection( int A )
{
    D3DXMATRIXA16 mRot;
    D3DXQUATERNION q;
    float fDistFromWalls = 0.0f;
    int nAngle = ( rand() % 360 );
    float fRotAngle = 0.0f;
    while( fDistFromWalls < 1.0f )
    {
        nAngle += 62; nAngle %= 360;
        fRotAngle = ( nAngle / 360.0f ) * D3DX_PI * 2.0f;
        D3DXQuaternionRotationYawPitchRoll( &q, fRotAngle, 0.0f, 0.0f );
        D3DXMatrixRotationQuaternion( &mRot, &q );
        D3DXVECTOR3 vVel = D3DXVECTOR3( mRot._31, mRot._32, mRot._33 );
        D3DXVECTOR3 vPos = g_GameState.DroidQ[A].vPosition;
        D3DXVECTOR3 vPosPlus = vPos + vVel;

        D3DXVECTOR3 vWallPtA = D3DXVECTOR3( g_MinBound.x, vPos.y, g_MinBound.z );
        D3DXVECTOR3 vWallPtB = D3DXVECTOR3( g_MaxBound.x, vPos.y, g_MinBound.z );
        D3DXVECTOR3 vWallPtC = D3DXVECTOR3( g_MinBound.x, vPos.y, g_MaxBound.z );
        D3DXVECTOR3 vWallPtD = D3DXVECTOR3( g_MaxBound.x, vPos.y, g_MaxBound.z );
        D3DXVECTOR3 vWallABNormal = D3DXVECTOR3( 0, 0, 1 );
        D3DXVECTOR3 vWallACNormal = D3DXVECTOR3( 1, 0, 0 );
        D3DXVECTOR3 vWallBDNormal = D3DXVECTOR3( 0, 0, -1 );
        D3DXVECTOR3 vWallCDNormal = D3DXVECTOR3( -1, 0, 0 );

        float fDistFromWallAB = GetDistFromWall( vPos, vPosPlus, vWallPtA, vWallABNormal );
        float fDistFromWallAC = GetDistFromWall( vPos, vPosPlus, vWallPtA, vWallACNormal );
        float fDistFromWallBD = GetDistFromWall( vPos, vPosPlus, vWallPtD, vWallBDNormal );
        float fDistFromWallCD = GetDistFromWall( vPos, vPosPlus, vWallPtD, vWallCDNormal );
        float fMin1 = min( fDistFromWallAB, fDistFromWallAC );
        float fMin2 = min( fDistFromWallBD, fDistFromWallCD );
        fDistFromWalls = min( fMin1, fMin2 );
    }

    g_GameState.DroidQ[A].fTargetRotation = fRotAngle;
    D3DXQuaternionRotationYawPitchRoll( &g_GameState.DroidQ[A].qTarget, g_GameState.DroidQ[A].fTargetRotation, 0.0f,
                                        0.0f );
    g_GameState.DroidQ[A].qStart = g_GameState.DroidQ[A].qCurrent;
    g_GameState.DroidQ[A].fRotInterp = 0.0f;
    g_GameState.DroidQ[A].aiState = AI_TURNING;
    g_GameState.DroidQ[A].vVelocity = D3DXVECTOR3( 0, 0, 0 );
    g_GameState.DroidQ[A].vNudgeVelocity = D3DXVECTOR3( 0, 0, 0 );
}

