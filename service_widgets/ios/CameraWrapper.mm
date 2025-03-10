#import "CameraWrapper.h"
#include <QGuiApplication>

@implementation CameraWrapper {
    UIImagePickerController *_picker;
    UIViewController *_rootViewController;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _rootViewController = [[UIApplication sharedApplication] keyWindow].rootViewController;
    }
    return self;
}

- (void)openCamera {
    if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        qWarning("Camera not available");
        return;
    }

    _picker = [[UIImagePickerController alloc] init];
    _picker.delegate = self;
    _picker.sourceType = UIImagePickerControllerSourceTypeCamera;
    _picker.cameraCaptureMode = UIImagePickerControllerCameraCaptureModePhoto;

    dispatch_async(dispatch_get_main_queue(), ^{
        [_rootViewController presentViewController:_picker animated:YES completion:nil];
    });
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info {
    UIImage *image = info[UIImagePickerControllerOriginalImage];
    NSURL *tempURL = [self saveImageToTempFile:image];

    if (tempURL && self.imageCaptured) {
        QString path = QString::fromNSString(tempURL.path);
        self.imageCaptured(path);
    }

    [picker dismissViewControllerAnimated:YES completion:nil];
    _picker = nil;
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [picker dismissViewControllerAnimated:YES completion:nil];
    _picker = nil;

    if (self.captureCancelled) {
        self.captureCancelled(); // Вызов callback при отмене
    }
}

- (NSURL *)saveImageToTempFile:(UIImage *)image {
    NSData *data = UIImageJPEGRepresentation(image, 0.9);
    NSString *fileName = [NSString stringWithFormat:@"%@.jpg", [[NSUUID UUID] UUIDString]];
    NSURL *tempURL = [NSURL fileURLWithPath:[NSTemporaryDirectory() stringByAppendingPathComponent:fileName]];

    if ([data writeToURL:tempURL atomically:YES]) {
        return tempURL;
    }
    return nil;
}

@end
