//
//  HXPhotoCommon.h
//  照片选择器
//
//  Created by 洪欣 on 2019/1/8.
//  Copyright © 2019年 洪欣. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HXPhotoConfiguration.h"
#import "HXPhotoDefine.h"
#import "HXPhotoModel.h"
#import "HXAlbumModel.h"
#if __has_include(<AFNetworking/AFNetworking.h>)
#import <AFNetworking/AFNetworking.h>
#elif __has_include("AFNetworking.h")
#import "AFNetworking.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 *  照片选择器的管理类, 使用照片选择器时必须先懒加载此类,然后赋值给对应的对象
 */
typedef NS_ENUM(NSUInteger, HXPhotoManagerSelectedType) {
    HXPhotoManagerSelectedTypePhoto = 0,        //!< 只显示图片
    HXPhotoManagerSelectedTypeVideo = 1,        //!< 只显示视频
    HXPhotoManagerSelectedTypePhotoAndVideo     //!< 图片和视频一起显示
};


typedef void (^ HXPhotoCommonGetUrlFileLengthSuccess)(NSUInteger length);
typedef void (^ HXPhotoCommonGetUrlFileLengthFailure)(void);

@interface HXPhotoCommon : NSObject
@property (strong, nonatomic, nullable) NSBundle *languageBundle;
/// 相册风格
@property (assign, nonatomic) HXPhotoStyle photoStyle;
@property (assign, nonatomic) HXPhotoLanguageType languageType;
@property (strong, nonatomic) UIImage *cameraImage;

/// 预览视频时是否自动播放
@property (assign, nonatomic) HXVideoAutoPlayType videoAutoPlayType;

/// 预览视频时是否先下载视频再播放
@property (assign, nonatomic) BOOL downloadNetworkVideo;

@property (assign, nonatomic) BOOL isVCBasedStatusBarAppearance;

@property (assign, nonatomic) BOOL isHapticTouch;

/**
 当前选择类型
 */
@property (assign, nonatomic) HXPhotoManagerSelectedType rCurType;

#if HasAFNetworking
@property (assign, nonatomic) AFNetworkReachabilityStatus netStatus;
@property (copy, nonatomic) void (^ reachabilityStatusChangeBlock)(AFNetworkReachabilityStatus netStatus);
#endif

@property (strong, nonatomic) HXAlbumModel * _Nullable cameraRollAlbumModel;

- (void)getURLFileLengthWithURL:(NSURL *)url
                        success:(HXPhotoCommonGetUrlFileLengthSuccess)success
                        failure:(HXPhotoCommonGetUrlFileLengthFailure)failure;

- (NSURLSessionDownloadTask * _Nullable)downloadVideoWithURL:(NSURL *)videoURL
                                          progress:(void (^ _Nullable)(float progress, long long downloadLength, long long totleLength, NSURL * _Nullable videoURL))progress
                                   downloadSuccess:(void (^ _Nullable)(NSURL * _Nullable filePath, NSURL * _Nullable videoURL))success
                                   downloadFailure:(void (^ _Nullable)(NSError * _Nullable error, NSURL * _Nullable videoURL))failure;

+ (instancetype)photoCommon;
+ (void)deallocPhotoCommon;
- (void)saveCamerImage;
- (BOOL)isDark;
@end

NS_ASSUME_NONNULL_END
