#include "AppDelegate.h"
#include "GameMainMenu.h"
#include "Network/NetworkManager.h"
#include "Game/Pawn.h"
#include "Network/ConstructorDatabase.h"
#include "Network/Messages/MessageDatabase.h"
#include "Network/LoadLevel.h"
#include "Network/Messages/JoinMessage.h"
#include "Network/ReplicateInstance.h"
#include "Network/ReplicateState.h"
#include "network/UDPGameSocket.h"

USING_NS_CC;

using mog::network::NetworkManager;
using mog::Pawn;

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

	mog::network::MessageDatabase::get()->registerMessage(new mog::network::LoadLevel());
	mog::network::MessageDatabase::get()->registerMessage(new mog::network::JoinMessage());
	mog::network::MessageDatabase::get()->registerMessage(new mog::network::ReplicateInstance());
	mog::network::MessageDatabase::get()->registerMessage(new mog::network::ReplicateState());
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
