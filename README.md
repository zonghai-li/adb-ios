# adb-ios
Android ADB on iOS

# Porting Details
- ADB client + server architecture on the iOS host side. the ADB server uses port 5037 as would normally do.
- ADB client exposes some essential methods for caller codes to integrate ADB functionalities.
- No USB supported

# Code Snippet

<pre><code>

// initialize the AdbClient
_adb = [[AdbClient alloc] init];

...

// connect to a device
[_adb connect:@"10.0.1.223" didResponse:^(bool succ, NSString *result) {
  NSLog("%d : %@", succ, result); 
}];

//install apk
NSString *apkPath = [[NSBundle mainBundle] pathForResource:@"Term" ofType:@"apk"];
[_adb installApk:apkPath flags:ADBInstallFlag_Replace didResponse:^(bool succ, NSString *result) {
    NSLog("%d : %@", succ, result);       
}];

// some shell commands
[_adb shell:@"pm list packages" didResponse:^(bool succ, NSString *result) {
  //...
}];

</code></pre>


