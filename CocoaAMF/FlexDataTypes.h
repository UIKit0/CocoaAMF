//
//  AMFFlexDataTypes.h
//  CocoaAMF
//
//  Created by Marc Bauer on 23.03.09.
//  Copyright 2009 nesiumdotcom. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSObject-AMFExtensions.h"
#if TARGET_OS_IPHONE
#import "NSObject-iPhoneExtensions.h"
#endif

typedef enum _FlexCommandMessageOperationType{
	kFlexCommandMessageSubscribeOperation = 0, 
	kFlexCommandMessageUnsubscribeOperation = 1, 
	kFlexCommandMessagePollOperation = 2, 
	kFlexCommandMessageClientSyncOperation = 4, 
	kFlexCommandMessageClientPingOperation = 5, 
	kFlexCommandMessageClusterRequestOperation = 7, 
	kFlexCommandMessageLoginOperation = 8, 
	kFlexCommandMessageLogoutOperation = 9, 
	kFlexCommandMessageSubscriptionInvalidateOperation = 10, 
	kFlexCommandMessageMultiSubscribeOperation = 11, 
	kFlexCommandMessageDisconnectOperation = 12, 
	kFlexCommandMessageTriggerConnectOperation = 13, 
	kFlexCommandMessageUnknownOperation = 1000
} FlexCommandMessageOperationType;


@interface FlexArrayCollection : NSObject <NSCoding>{
	NSArray *source;
}
@property (nonatomic, strong) NSArray *source;
+ (NSString *)AMFClassAlias;
- (id)initWithSource:(NSArray *)obj;
- (NSUInteger)count;
@end


@interface FlexObjectProxy : NSObject <NSCoding>{
	NSObject *object;
}
@property (nonatomic, strong) NSObject *object;
+ (NSString *)AMFClassAlias;
- (id)initWithObject:(NSObject *)obj;
@end


@interface FlexAbstractMessage : NSObject <NSCoding>{
	NSObject *body;
	NSString *clientId;
	NSString *destination;
	NSDictionary *headers;
	NSString *messageId;
	NSTimeInterval timeToLive;
	NSTimeInterval timestamp;
}
@property (nonatomic, strong) NSObject *body;
@property (nonatomic, strong) NSString *clientId;
@property (nonatomic, strong) NSString *destination;
@property (nonatomic, strong) NSDictionary *headers;
@property (nonatomic, strong) NSString *messageId;
@property (nonatomic, assign) NSTimeInterval timeToLive;
@property (nonatomic, assign) NSTimeInterval timestamp;
+ (NSString *)AMFClassAlias;
@end


@interface FlexAsyncMessage : FlexAbstractMessage{
	NSString *correlationId;
}
@property (nonatomic, strong) NSString *correlationId;
@end


@interface FlexCommandMessage : FlexAsyncMessage{
	FlexCommandMessageOperationType operation;
}
@property (nonatomic, assign) FlexCommandMessageOperationType operation;
@end


@interface FlexAcknowledgeMessage : FlexAsyncMessage{
}
@end


@interface FlexErrorMessage : FlexAcknowledgeMessage{
	NSObject *extendedData;
	NSString *faultCode;
	NSString *faultDetail;
	NSString *faultString;
	NSObject *rootCause;
}
@property (nonatomic, strong) NSObject *extendedData;
@property (nonatomic, strong) NSString *faultCode;
@property (nonatomic, strong) NSString *faultDetail;
@property (nonatomic, strong) NSString *faultString;
@property (nonatomic, strong) NSObject *rootCause;
+ (FlexErrorMessage *)errorMessageWithError:(NSError *)error;
@end


@interface FlexRemotingMessage : FlexAbstractMessage{
	NSString *operation;
	NSString *source;
}
@property (nonatomic, strong) NSString *operation;
@property (nonatomic, strong) NSString *source;
@end