
#pragma once

#include "ofMain.h"
#include "ofImage.h"
#include "BaseMediaSource.h"
#include "Types.h"

#include "Poco/URI.h"

// forward declaration
class BaseMediaSource;

class BaseMediaAsset {
	
public:
	
	// BASE Materials
	// ----------------------------------------------------------------------------------------------------
	BaseMediaAsset(MediaAssetType assetType, string assetURI);		// set image cache
	virtual ~BaseMediaAsset();
	
	// ----------------------------------------------------------------------------------------------------
	void setAssetId(string id);
	string getAssetId();
	
	Poco::URI getAssetURI();
	
	// BASE Materials
	// ----------------------------------------------------------------------------------------------------
	
	MediaAssetType getAssetType();	// this returns an enum type
	
	// CACHING
	// ----------------------------------------------------------------------------------------------------
	
	// do the caching
	virtual void createCache() = 0;         // caches are created differently depending on the source
	void	clearCache();					// removes all of the cached images
	
	
	void setCacheImageSize(int width, int height);	// set the size of the images to cache
	void setCacheFPS(int fps);				// how many images to cache / second
	float getCacheFPS();					// what is the fps of this cache?
	
	ofImage* getCacheImageAtPosition(float f);	// f should be a number between 0, 1
	ofImage* getCacheImage();					// get the default preview image
	
	
	// ACTIVE INSTANCES
	// ----------------------------------------------------------------------------------------------------
	bool removeActiveInstance(BaseMediaSource* instance);
	bool addActiveInstance(BaseMediaSource* instance);
	vector<BaseMediaSource*>* getInstances();
	bool hasAnyActiveInstances();
	bool hasInstance(BaseMediaSource* instance);

	// 
	
	
protected:
	
    MediaAssetType assetType;
	Poco::URI	assetURI;		// the URI for the source (could be a stream or url, or id, etc)
	
	bool generateAssetID();
	string assetID; // this is generated
	
	// bool isSharable; // any asset can be shared
	
	vector<BaseMediaSource*> activeInstances;
	
	// cache
	int cacheWidth, cacheHeight; // should always be small
	bool isCached;
	float cacheFPS;
	
	vector<ofImage*> imageCache;
	
	
	int bufferSize;
	bool isBuffered;
	bool isBuffering;
	//RingBuffer<ofImage*> buffer;
	//public clearBuffer();
	
	// meta data keywords
	vector<string> keywords;
	
	
};


//	----------------------------------------------------------------------------------------------------
class ImageMediaAsset : public BaseMediaAsset {
	
public:
	
	ImageMediaAsset(string assetURI) : BaseMediaAsset(MEDIA_ASSET_IMAGE, assetURI) {
		createCache();
	}
	~ImageMediaAsset() {
		ofLog(OF_LOG_VERBOSE, "Image asset " + assetID + " being destroyed");
	};
	
	void createCache() {
		
		// TODO: generate or load previews here
		
		ofImage* of = new ofImage(); // this must be deleted by the owner!
		of->loadImage("application/cache/media/images/default_image.png");
		imageCache.push_back(of);
		
		ofLog(OF_LOG_VERBOSE, "Creating image cache");
	}
	
	ofImage image;
	
};


//	----------------------------------------------------------------------------------------------------
class VideoMediaAsset : public BaseMediaAsset {
	
public:
	
	VideoMediaAsset(string assetURI) : BaseMediaAsset(MEDIA_ASSET_VIDEO, assetURI) {
		createCache();
	}
	~VideoMediaAsset() {}
	
	void createCache() {
		
		// TODO: generate or load previews here
		
		ofImage* of = new ofImage(); // this must be deleted by the owner!
		of->loadImage("application/cache/media/videos/default_video.png");
		imageCache.push_back(of);
		
		ofLog(OF_LOG_VERBOSE, "Creating video cache");
	}
	
	ofVideoPlayer video;
	
};


//	----------------------------------------------------------------------------------------------------
class GrabberMediaAsset : public BaseMediaAsset {
	
public:
	
	GrabberMediaAsset(string assetURI) : BaseMediaAsset(MEDIA_ASSET_GRABBER, assetURI) {
		createCache();
	}
	~GrabberMediaAsset() {}
	
	void createCache() {
		
		// TODO: generate or load previews here
		
		ofImage* of = new ofImage(); // this must be deleted by the owner!
		of->loadImage("application/cache/media/grabbers/default_grabber.png");
		imageCache.push_back(of);
		
		
		ofLog(OF_LOG_VERBOSE, "Creating grabber cache");
	}
	
	ofVideoGrabber grabber;

};

//	----------------------------------------------------------------------------------------------------
class StreamMediaAsset : public BaseMediaAsset {
	
public:
	
	StreamMediaAsset(string assetURI) : BaseMediaAsset(MEDIA_ASSET_STREAM, assetURI) {
		createCache();
	}
	~StreamMediaAsset() {}
	
	void createCache() {
		
		ofImage* of = new ofImage(); // this must be deleted by the owner!
		of->loadImage("application/cache/media/streams/default_stream.png");
		imageCache.push_back(of);
		
		
		ofLog(OF_LOG_VERBOSE, "Creating stream cache");

	}
	
	//ofxVideoStreamer streamer;
};








