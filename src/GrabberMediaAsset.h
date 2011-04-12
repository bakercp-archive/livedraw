

#pragma once

#include "BaseMediaAsset.h"

//	----------------------------------------------------------------------------------------------------
class GrabberMediaAsset : public BaseMediaAsset {
	
public:
	
	GrabberMediaAsset(string assetURI) : BaseMediaAsset(MEDIA_ASSET_GRABBER, assetURI) {
		createCache();
	}
	~GrabberMediaAsset() {}
	
	void createCache();	
    
};

