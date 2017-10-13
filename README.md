# Iron-Lion
Game engine demo made from a directX(9&10) sample (XACTGame is the name of the root from sdk's demo)

The purpose is to learn the DirectX Sdk step by step , through a little game :
( Based over an Audio demo , featuring XACT technology )
But also to practice some cool stuff , like AI , Physics , Networking , Audio etc ...
The goal being to study the case of a complete Game engine .

Parts of the future GameEngine :

* GUI : Using DXUTgui from DX sdk
* AUDIO : Using XACT3 from DX sdk
* INPUT : Using XInput and DirectInput Side by Side from DX sdk
  (which allows applications to interact with the Xbox 360 Controller when it is connected to a Windows PC.
)
* RENDERING 3D  : Using Directx api
* PHYSICS       : Using ... Bullet or other .
* NETWORK       : Not defined yet ...
* AI LOGICS     : Using FSM techniques and more...
* SCRIPTING     : USING LUA ( https://github.com/vinniefalco/LuaBridge , https://eliasdaler.wordpress.com/2014/07/18/using-lua-with-cpp-luabridge/ )

TODO : 
_USE XNA collision lib instead of actual simpliest code for walls ...
_Use SkinMesh template in directx file to describe vertex groups for precise collision check


FAQ
************************

# Why Iron-Lion as title ?

Because that demo context is in an arena , with iron bots as opponents . 
So the player will have to be like a lion front of these iron(ic) behaviors... lol 

# Is it only for Windows ?

Yes , and linked on an XPwin32 machine with Msvc9 Express .

# No OpenGl ?

Not this time , this is a directX study ...

