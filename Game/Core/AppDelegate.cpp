#include "AppDelegate.h"
#include "GameMainMenu.h"
#include "Engine/Network/NetworkManager.h"

#include "Engine/Network/ConstructorDatabase.h"
#include "Engine/Network/Messages/MessageDatabase.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/JoinMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/Messages/ReplicateStateMessage.h"
#include "Engine/Network/Messages/RemoteMethodCallMessage.h"
#include "Engine/Network/UDPGameSocket.h"
#include "Engine/Network/NetworkPawnFactory.h"
#include "Engine/Core/LevelFactory.h"
#include "Engine/Core/LevelDatabase.h"

#include "Core/Pawn.h"
#include "Core/GameLevel.h"

USING_NS_CC;

using mog::network::NetworkManager;
using mog::Pawn;

using mog::network::LoadLevelMessage;
using mog::network::JoinMessage;
using mog::network::ReplicateStateMessage;
using mog::network::ReplicateInstanceMessage;
using mog::network::RemoteMethodCallMessage;

using mog::GameLevel;


AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
	
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {


    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
		glview->setFrameSize(683, 600);
        director->setOpenGLView(glview);
    }


	//auto designSize = Size(683, 768);
	//glview->setDesignResolutionSize(designSize.width, designSize.
		//height, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = mog::GameMainMenu::createScene();

    // run
    director->runWithScene(scene);

	REGISTER_CONSTRUCTOR(Pawn);


	REGISTER_MESSAGE(LoadLevelMessage);
	REGISTER_MESSAGE(JoinMessage);
	REGISTER_MESSAGE(ReplicateInstanceMessage);
	REGISTER_MESSAGE(ReplicateStateMessage);
	REGISTER_MESSAGE(RemoteMethodCallMessage);

	REGISTER_LEVEL(GameLevel);

	mog::network::NetworkPawnFactory::get()->setNetworkPawn<Pawn>();
	mog::network::UDPGameSocket::setup();
	//TODO: mog::network::UDPGameSocket::teardown()

	mog::LevelFactory::get()->setObject<mog::GameLevel>();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    //Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

}
