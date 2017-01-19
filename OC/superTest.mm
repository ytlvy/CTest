#import <Foundation/Foundation.h>
#import <objc/message.h>

@interface A : NSObject @end
@interface B : A @end
@interface C : B @end
@interface X : NSObject @end

@implementation A 
- (void)abc
{
	NSLog(@"-[A abc] called from class %@", NSStringFromClass([self class]));
}
@end

@implementation B
@end

@implementation C
- (void)abc
{
	NSLog(@"-[C abc] called from class %@", NSStringFromClass([self class]));
}
@end

@implementation X
-(void)A_abc
{
	struct objc_super sup = {self, [A class]};
	objc_msgSendSuper(&sup, @selector(abc));
}
-(void)B_abc
{
	struct objc_super sup = {self, [B class]};
	objc_msgSendSuper(&sup, @selector(abc));
}
-(void)C_abc
{
	struct objc_super sup = {self, [C class]};
	objc_msgSendSuper(&sup, @selector(abc));
}
@end

int main(int argc, char *argv[])
{
	@autoreleasepool {
		[[X new] A_abc];
		[[X new] B_abc];
		[[X new] C_abc];
	}
}