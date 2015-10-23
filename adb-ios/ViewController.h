//
//  ViewController.h
//  adb-ios
//
//  Created by Li Zonghai on 9/28/15.
//  Copyright (c) 2015 Li Zonghai. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController


@property(strong, nonatomic) IBOutlet UITextView *textview;

-(IBAction)connectBtn:(id)sender;
-(IBAction)installApkBtn:(id)sender;
-(IBAction)uninstallApkBtn:(id)sender;
-(IBAction)startApk:(id)sender;
-(IBAction)disconnect:(id)sender;
-(IBAction)ps:(id)sender;
-(IBAction)list:(id)sender;
@end

