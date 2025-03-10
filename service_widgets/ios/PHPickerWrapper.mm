#import "PHPickerWrapper.h"
#include <QGuiApplication>

@implementation PHPickerWrapper {
    PHPickerViewController *_picker;
    UIViewController *_rootViewController;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _rootViewController = [[UIApplication sharedApplication] keyWindow].rootViewController;
    }
    return self;
}

- (void)openPHPickerWithMultipleSelection:(BOOL)allowMultiple {
    PHPickerConfiguration *config = [[PHPickerConfiguration alloc] init];
    config.selectionLimit = allowMultiple ? 0 : 1; // 0 = без ограничений
    config.filter = [PHPickerFilter imagesFilter]; // Только изображения

    _picker = [[PHPickerViewController alloc] initWithConfiguration:config];
    _picker.delegate = self;

    dispatch_async(dispatch_get_main_queue(), ^{
        [_rootViewController presentViewController:_picker animated:YES completion:nil];
    });
}

- (void)picker:(PHPickerViewController *)picker didFinishPicking:(NSArray<PHPickerResult *> *)results {
    [picker dismissViewControllerAnimated:YES completion:nil];

    if (results.count == 0) {
        qDebug() << "Выбор отменен или файлы не выбраны";
        if (self.filesSelected) {
            self.filesSelected(QStringList()); // Испускаем сигнал с пустым списком
        }
        _picker = nil;
        return;
    }

    NSMutableArray<NSItemProvider *> *providers = [NSMutableArray new];
    for (PHPickerResult *result in results) {
        [providers addObject:result.itemProvider];
    }

    // Конвертируем NSItemProvider в пути к файлам
    [self processItemProviders:providers];
    _picker = nil;
}

- (void)processItemProviders:(NSArray<NSItemProvider *> *)providers {
    dispatch_group_t group = dispatch_group_create();
    NSMutableArray<NSString *> *filePaths = [NSMutableArray new];

    for (NSItemProvider *provider in providers) {
        if (![provider canLoadObjectOfClass:[UIImage class]]) continue;

        dispatch_group_enter(group);
        [provider loadObjectOfClass:[UIImage class] completionHandler:^(__kindof id<NSItemProviderReading>  _Nullable object, NSError * _Nullable error) {
            if ([object isKindOfClass:[UIImage class]]) {
                UIImage *image = (UIImage *)object;
                NSURL *tempURL = [self saveImageToTempFile:image];
                if (tempURL) {
                    [filePaths addObject:tempURL.path];
                }
            }
            dispatch_group_leave(group);
        }];
    }

    dispatch_group_notify(group, dispatch_get_main_queue(), ^{
        QStringList paths;
        for (NSString *path in filePaths) {
            paths.append(QString::fromNSString(path));
        }

        if (self.filesSelected) {
            self.filesSelected(paths);
        }
    });
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
