#import <Foundation/Foundation.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	@autoreleasepool {
		NSUInteger i = 10;
		NSUInteger j = 8;
		
		j -= i;
		NSInteger k = j - i;
		cout<<j<<"    "<<k<<endl;
		if((j-i) > 0) {
			NSLog(@"大于");
		} 
		
	}
}