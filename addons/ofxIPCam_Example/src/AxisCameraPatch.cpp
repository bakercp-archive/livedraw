
#import "AxisCameraPatch.h"
//#import "QCImage.h"

//#include <Foundation/Foundation.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include "ofMain.h"

#define BUFFER_SIZE (1024*1024*2)

CFHTTPMessageRef request;
CFReadStreamRef readStream;
static unsigned char *bufferdata;
unsigned char * pixels = NULL;

static unsigned int head, tail;

CGContextRef cgctx = NULL;

static bool newFrame = false;

bool receiveAnyData = false;

static void
handleStreamEvent(CFReadStreamRef readStream, CFStreamEventType type, void * clientCallBackInfo);
CGContextRef CreateARGBBitmapContext (CGImageRef inImage);

static int parseSize(const unsigned char*buf, unsigned int *length){
	int size = 0, i = 0;
	while(buf[i] <= '9' && buf[i] >= '0' && i < 8)
	{
		size *= 10;
		size += buf[i] - '0';
		++i;
	}
	*length = i;
	//printf("parsing size %d\n",size);
	return size;
}

//http://thebends.googlecode.com/svn/trunk/ypeer/peers.cpp

void AxisCameraPatch::setSize(int w, int h) {
	imageWidth = w;
	imageHeight = h;
}

void AxisCameraPatch::end(){
	if (request){
		CFRelease(request);
		request = NULL;
	}
	delete bufferdata;

	bufferdata = NULL;
	head = tail = 0;
}


unsigned char * AxisCameraPatch::getPixels(){
	
	//if(true) return NULL;
	//Change order of pixels
	
	
	
	if(pixels) {
		
		for (int i = 0; i < (imageWidth*imageHeight); i++)
		{
			// ABGR to RBG
			RGB_Axispixels[i*3+0] = pixels[i*4+3]; // R 
			RGB_Axispixels[i*3+1] = pixels[i*4+2]; // G
			RGB_Axispixels[i*3+2] = pixels[i*4+1]; // B
		}
		
		
		/*
		for (int i = 0; i < (imageWidth*imageHeight*4)-4; i+=4) {
			//RGB_Axispixels[i] = pixels[i];
			RGB_Axispixels[i+0] = pixels[i+0];
			RGB_Axispixels[i+1] = pixels[i+3];
			RGB_Axispixels[i+2] = pixels[i+2];
			RGB_Axispixels[i+3] = pixels[i+1];
		}
		 */
	} else {
		//printf("RETURNING NULL\n");
		return NULL;
	}
	
	
	return RGB_Axispixels;
}

bool AxisCameraPatch::getReceiveAnyData(){
	return receiveAnyData;
}

void AxisCameraPatch::execute(string camUrl, int width, int height) {
	
	this->imageWidth = width;
	this->imageHeight = height;
	
	RGB_Axispixels = new unsigned char[imageWidth*imageHeight*3];
	
	bufferdata = new unsigned char[BUFFER_SIZE];
	head = tail = 0;
	
	/*NSString *path = [NSString stringWithFormat:@"http://blah.blah"];
	path = [path stringByAppendingString:@"/mjpg/video.mjpg"];
	NSURL *url = [NSURL URLWithString: path];
	if(!url)	// not a valid URL
		return YES;
	if(request)
		CFRelease(request);
	 */
	CFURLRef base_url_;

	//string myurl = "http://magiccam4.local/mjpg/video.mjpg";
	//string myurl = camUrl + "/mjpg/video.mjpg";
	string myurl = camUrl;

	CFURLRef url = CFURLCreateWithBytes(kCFAllocatorDefault,
									(const UInt8 *) myurl.c_str(),
									myurl.size(), 
									kCFStringEncodingUTF8,
									base_url_);

	request = CFHTTPMessageCreateRequest(NULL, CFSTR("GET"), (CFURLRef)url, kCFHTTPVersion1_1);
		
	printf("created request\n");
	loadRequest();
}

void AxisCameraPatch::loadRequest(){
	cancelLoad();
	readStream = CFReadStreamCreateForHTTPRequest(NULL, request);
	CFStreamClientContext   context  = { 0, this, NULL, NULL, NULL };
	CFReadStreamSetClient(readStream, 
						  kCFStreamEventHasBytesAvailable | 
						  kCFStreamEventEndEncountered | 
						  kCFStreamEventErrorOccurred, 
						  handleStreamEvent, 
						  &context);

	// RunLoops and QCRenderer don't always get along -- this will work as long as the application has a running main runloop (almost all cocoa apps).
	// CurrentRunLoop on a QCRenderer will simply stall -- stuff never gets processed.
	// perhaps in the future, we should create/manage our own runloop for this?
	
	///Users/zach/Documents/projects/teaching/OF 
	// workshop/of_preRelease_v0.05_xcode/apps/marcoAxisWork/_emptyExample/src/AxisCameraPatch.cpp:90: error: 
	// 'CFRunLoopGetMain' was not declared in this scope

	
	CFReadStreamScheduleWithRunLoop(readStream, /*CFRunLoopGetCurrent()*/ CFRunLoopGetMain(), kCFRunLoopCommonModes);
	CFReadStreamOpen(readStream);	
}

void AxisCameraPatch::cancelLoad(){
	if (readStream)
	{
		CFReadStreamClose(readStream);
		CFReadStreamSetClient(readStream, kCFStreamEventNone, NULL, NULL);
		CFReadStreamUnscheduleFromRunLoop(readStream, CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
		CFRelease(readStream);
		readStream = NULL;
	}
}	

static void handleStreamEvent(CFReadStreamRef readStream, CFStreamEventType type, void * clientCallBackInfo)
{
	
	//printf("GOT STREAM EVENT\n");
	
	//CFNetworkLoader *self = (CFNetworkLoader *)clientCallBackInfo;
	//NSLog(@"loadEvent: %i", type);
	//NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	CFHTTPMessageRef responseHeaders = (CFHTTPMessageRef)CFReadStreamCopyProperty(readStream, kCFStreamPropertyHTTPResponseHeader);
	
	if (responseHeaders) {
		// Is the server response an challenge for credentials?
		if(CFHTTPMessageGetResponseStatusCode(responseHeaders) == 401)
		{
			((AxisCameraPatch*)clientCallBackInfo)->cancelLoad();
			//[self cancelLoad];
			printf("auth challenge.  status code: %i)", CFHTTPMessageGetResponseStatusCode(responseHeaders));
			//NSLog(@"auth challenge.  status code: %i)", CFHTTPMessageGetResponseStatusCode(responseHeaders));
		
			CFStringRef userName;
			userName = CFStringCreateWithCString(NULL, "admin",
											kCFStringEncodingMacRoman);
			CFStringRef passWord;
			passWord = CFStringCreateWithCString(NULL, "powerful",
												 kCFStringEncodingMacRoman);
			
			
			if (CFHTTPMessageAddAuthentication(request, responseHeaders, userName, passWord, NULL, false))
			{
				printf("success!\n");
				//NSLog(@"success");
				((AxisCameraPatch*)clientCallBackInfo)->loadRequest();
				//[self loadRequest];
			}
			else	// this shouldn't happen, unless we can't auth for some weird reason..
			{
				printf("failure!\n");
			}
		}
		CFRelease(responseHeaders);
	}
	if(type == kCFStreamEventHasBytesAvailable)
	{
		
		//printf("--------------\n\n");
		//printf("bytes available\n");
		
		// annoying side effect:  if 3rd arg to CFReadStreamRead is zero, it closes 
		// the connection... so we have to make sure that doesn't happen eventually
		if(tail < BUFFER_SIZE)
		{
			int bytesRead = CFReadStreamRead(readStream, (UInt8*)bufferdata+tail, BUFFER_SIZE-tail);
			//printf("read %i bytes (%02x %02x) (%x %x %x)\n\n", bytesRead, bufferdata[0], bufferdata[1], head, tail, 1024*1024*2-tail);
			tail+=bytesRead;
		}
		
		
		
		// Check for complete images (parse header, check head/tail offsets) -- use the last complete image for the output, discarding intermediates
		// (intermediates mean we're falling behind, so we drop them to stay current)
		// Typical headers are about 68 bytes, but this can vary a little bit (since the reported length is a string, it can be 1 or more digits long, typically 4 or 5)
		// Headers end with two newlines (0x0d, 0x0a, 0x0d, 0x0a), which is 4 more bytes
		// additionally, there's a newline at the end of the jpeg data (0x0D, 0x0A) before the next header
		if(tail - head > 1000)	// less than this, and we certainly don't have a full image
		{
			// pedantic checks (remove for a tiny speed-up, at the risk of flying blind, more or less -- bad idea)
			
			//printf("1. >>\n%s\n",bufferdata);//+head+12);
			//printf("2. >>\n%s\n",bufferdata);//+head+14);
			//printf("3. >>\n%s\n",bufferdata);//+head+40);
			
			
			
			//if(strncmp((char*)bufferdata+head, "--ipcamera", 10)
            if(strncmp((char*)bufferdata+head, "--myboundary", 12) ||
				strncmp((char*)bufferdata+head+14,"Content-Type: image/jpeg",24) ||
				strncmp((char*)bufferdata+head+40,"Content-Length: ",16))
			{
				printf("oh crap, lost sync OR content-length is not here... (%p %x)\n", bufferdata, head);
				// here we could do something graceful, like manually scan for the boundary flag, and then reset head/tail...
				// let's wait to see if it happens in the wild, first (might indicate other errors as well)
			}
			else	// in sync (common case)
			{
				
				//printf ("so far so good \n");

				//NSLog(@"so far, so good...");
				unsigned int length = 0, size = 0;
				unsigned char* data = NULL;
			
				//printf("buffdata=%s\n",bufferdata);
				
				

				while((head+56+4+length+size+2) < tail)
				{
					
					
					size = parseSize(bufferdata+head+56, &length);
					
					// correctly parsed!
					
					
					
					
					if( (head+56+4+length+size+2) < tail )
					{
						//if(data)
						//	NSLog(@"dropping a frame");
						
						//printf("dropping frame!!!!!!!!!!!\n");
						
						data = bufferdata+head+56+4+length;
						head += 56+4+length+size+2;
					}
				}
				
				

				
				if(data)
				{
					// do some magic here 
					printf ("got the image: \n");
					receiveAnyData = true;
					
					
					CFDataRef cfData  = CFDataCreateWithBytesNoCopy (
														   NULL,
														   data,
														   size,
														   kCFAllocatorNull);
					
					
					
					CGDataProviderRef cgData = CGDataProviderCreateWithCFData(cfData);
					
					CGImageRef m_cgImageRef = CGImageCreateWithJPEGDataProvider(cgData,
																	 NULL,
																	 false,
																	 kCGRenderingIntentDefault);
					
					
					// CREATE ARGB BITMAP CONTEXT
					if (cgctx == NULL) 
					{ 
						//printf("cgctx was null\n");
						cgctx = CreateARGBBitmapContext(m_cgImageRef);
					}
					
					
					
					
					
					// Get image width, height. We'll use the entire image.
					size_t w = CGImageGetWidth(m_cgImageRef);
					size_t h = CGImageGetHeight(m_cgImageRef);
					CGRect rect = {{0,0},{w,h}}; 
					
					//imageWidth = w;
					//imageHeight = h;
					
					
//					printf("W=%d H=%d\n",w,h);
					
					/*if (pixels == NULL){
						pixels = new unsigned char [w*h*4];
					}*/
					// Draw the image to the bitmap context. Once we draw, the memory 
					// allocated for the context for rendering will then contain the 
					// raw image data in the specified color space.
					CGContextDrawImage(cgctx, rect, m_cgImageRef); 
					
					void *data = CGBitmapContextGetData (cgctx);
					pixels = (unsigned char *) data;
					
					CGImageRelease( m_cgImageRef);
					//printf("%i \n", pixels[1]);
					
					newFrame = true;
					printf("NEW FRAME!\n");
					
					/*NSData *jpegData = [NSData dataWithBytesNoCopy:data length: size freeWhenDone: NO];
					CIImage *jpeg = [CIImage imageWithData: jpegData];*/
					//QCImage *img = [[QCImage alloc] initWithCIImage: jpeg options: nil];
					//[outputImage setImageValue: img];
					//[img release];					
				}
/*				
#if 0	// this version doesn't discard frames -- easier to follow, but can lag into oblivion under load
				size = parseSize(bufferdata+head+56, &length);
				//NSLog(@"image size is %i bytes (%i length), tail's at %i", size, length, tail);
				
				// 56 = fixed header size, 4 = 2 newlines, length = length of ContentLength string, size = image data size, 2 = trailing newline
				if( (head+56+4+length+size+2) < tail )
				{
					NSData *jpegData = [NSData dataWithBytesNoCopy:bufferdata+head+56+4+length length: size freeWhenDone: NO];
					CIImage *jpeg = [CIImage imageWithData: jpegData];
					QCImage *img = [[QCImage alloc] initWithCIImage: jpeg options: nil];
					[outputImage setImageValue: img];
					[img release];
					
					head += 56+4+length+size+2;
				}
#endif
*/ 
			}
		}
		
		// if head is past the half-way mark, move all the data back to the front, to make room in the bufferdata
		if(head >= BUFFER_SIZE/2)
		{
			memmove(bufferdata, bufferdata+head, tail-head);
			tail -= head;
			head = 0;
		}
		
	}
	else if(type == kCFStreamEventEndEncountered)
	{
		printf("stream ended... lost connection? \n");
	}
	
}





CGContextRef CreateARGBBitmapContext (CGImageRef inImage)
{
    CGContextRef    context = NULL;
    CGColorSpaceRef colorSpace;
    void *          bitmapData;
    int             bitmapByteCount;
    int             bitmapBytesPerRow;
	
	// Get image width, height. We'll use the entire image.
    size_t pixelsWide = CGImageGetWidth(inImage);
    size_t pixelsHigh = CGImageGetHeight(inImage);
	
    // Declare the number of bytes per row. Each pixel in the bitmap in this
    // example is represented by 4 bytes; 8 bits each of red, green, blue, and
    // alpha.
    bitmapBytesPerRow   = (pixelsWide * 4);
    bitmapByteCount     = (bitmapBytesPerRow * pixelsHigh);
	
    // Use the generic RGB color space.
    colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    if (colorSpace == NULL)
    {
        fprintf(stderr, "Error allocating color space\n");
        return NULL;
    }
	
    // Allocate memory for image data. This is the destination in memory
    // where any drawing to the bitmap context will be rendered.
    bitmapData = malloc( bitmapByteCount );
    if (bitmapData == NULL) 
    {
        fprintf (stderr, "Memory not allocated!");
        CGColorSpaceRelease( colorSpace );
        return NULL;
    }
	
    // Create the bitmap context. We want pre-multiplied ARGB, 8-bits 
    // per component. Regardless of what the source image format is 
    // (CMYK, Grayscale, and so on) it will be converted over to the format
    // specified here by CGBitmapContextCreate.
    context = CGBitmapContextCreate (bitmapData,
									 pixelsWide,
									 pixelsHigh,
									 8,      // bits per component
									 bitmapBytesPerRow,
									 colorSpace,
									 kCGImageAlphaPremultipliedFirst);
    if (context == NULL)
    {
        free (bitmapData);
        fprintf (stderr, "Context not created!");
    }
	
    // Make sure and release colorspace before returning
    CGColorSpaceRelease( colorSpace );
	
    return context;
}
 
/*
 //http://developer.apple.com/qa/qa2007/qa1509.html
*/