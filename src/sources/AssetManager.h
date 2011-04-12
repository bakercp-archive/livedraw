/*
 *  SourceManager.h
 *  livedraw
 *
 *  Created by Christopher P. Baker on 1/15/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#pragma once

#include "ofxXmlSettings.h"
#include "ofxDirList.h"
#include "ofImage.h"

#include "BaseMediaAsset.h"

/*
#include "GrabberSource.h"
#include "VideoSource.h"
#include "ImageSource.h"
#include "StreamSource.h"
*/
 
class AssetManager { //: public OscNodeListener {
	
public:
	
	AssetManager();
	~AssetManager();

	
	// this is for sources (videos)
	//void getSourceInstance(BaseMediaSource* source);
	
	// this is for shared sources (live video, streams, videos??) // if we loaded the video into memory
	//void getSourceShared(BaseMediaSource* source);
	
	//bool addSource(BaseMediaSource* source);
	//bool removeSource(BaseMediaSource* source);
	
	
	void loadAssets();
	
	void loadImages();
	void loadVideos();
	void loadGrabbers();
	void loadStreams();
	
	
	int getNumImageAssets();
	int getNumVideoAssets();
	int getNumGrabberAssets();
	int getNumStreamAssets();

	//  TODO: for file watchers	
	//	void onNewAsset(ImageMediaAsset* image);
	//	void onNewAsset(VideoMediaAsset* video);
	//	void onNewAsset(GrabberMediaAsset* grabber);
	//	void onNewAsset(StreamMediaAsset* stream);
	
	

    
	// TODO: this is strange.  we should be able to open this without having it passed in
	void setDirList(ofxDirList* dir);
	ofxDirList*   aaa;

private:
	
	vector<ImageMediaAsset*> images;
	vector<VideoMediaAsset*> videos ;
	vector<GrabberMediaAsset*> grabbers;
	vector<StreamMediaAsset*> streams;
	
		

};
