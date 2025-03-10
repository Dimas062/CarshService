#import <UIKit/UIKit.h>
#include <QObject>
#include <QString>

@interface CameraWrapper : NSObject <UINavigationControllerDelegate, UIImagePickerControllerDelegate>

@property (nonatomic, assign) void (*imageCaptured)(const QString &);
@property (nonatomic, assign) void (*captureCancelled)(); // Новый callback для отмены
- (void)openCamera;

@end
