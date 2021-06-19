//clang -rewrite-objc block1.c

#include <stdio.h>
#import <Foundation/Foundation.h>

typedef void(^TestBlkDef)();

int main(int argc, char *argv[]) {
	__block int i = 0;
	NSString *s = @"111";
	TestBlkDef blk = ^(){
		i++;
		NSLog(@"%@", s);
	};
	
	TestBlkDef blkcopy = [blk copy];
	blkcopy = [blkcopy copy];
	
	TestBlkDef blk2 = ^() {
		blk();
	};
	
	blk2();
	}