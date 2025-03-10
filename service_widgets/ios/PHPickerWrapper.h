#import <PhotosUI/PhotosUI.h>
#include <QObject>
#include <QStringList>

typedef void (*PHPickerCallback)(const QStringList &);

@interface PHPickerWrapper : NSObject <PHPickerViewControllerDelegate>

@property (nonatomic, assign) PHPickerCallback filesSelected;
- (void)openPHPickerWithMultipleSelection:(BOOL)allowMultiple;

@end